#include <time.h>
#include <QTextStream>
#include "Minimax.h"
#include "Move.h"
#include "Board.h"
#include "BoardEvaluator.h"

const static double MAX_VALUE = 1e10;
const static double MIN_VALUE = -1e10;

Minimax::Minimax()
{
    m_boardEvaluator = nullptr;
}

Minimax::~Minimax()
{

}


int Minimax::getNumboardsEvaluated()
{
    return 0;
}

Move* Minimax::execute(const Board* board, int depth)
{
    double currentValue;

    clock_t start, end;
    start = clock();

    Move* bestMove = nullptr;
    double hightestSeenValue = MIN_VALUE;
    double lowestSeenValue = MAX_VALUE;

    QTextStream out(stdout);
    out << board->getMoveMaker() << " IS THINKING with depth " << depth <<endl;

    CollectMove moves = board->getLegalMoves();

//    int numMoves = static_cast<int>(moves.size());

    for (Move* move: moves) {

        Board* transitionBoard = move->Execute();

        currentValue = transitionBoard->getMoveMaker() == Alliance::WHITE ?
                    min(transitionBoard, depth - 1): max(transitionBoard, depth - 1);

        if(board->getMoveMaker() == Alliance::WHITE && currentValue >= hightestSeenValue)
        {
            hightestSeenValue = currentValue;
            bestMove = move;
        }
        else if(board->getMoveMaker() == Alliance::BLACK && currentValue <= lowestSeenValue)
        {
            lowestSeenValue = currentValue;

            if(bestMove)
                delete bestMove;

            bestMove = move;
        }
        // release memory
        else
        {
            delete move;
        }

        delete transitionBoard;
    }


    /* Do the work. */
    end = clock();
    m_executeTime = static_cast<double>((end-start)/ CLOCKS_PER_SEC);

    return bestMove;
}

double Minimax::min(const Board* board, int depth) const
{
    if(depth == 0/*|| game over*/)
    {
        return this->m_boardEvaluator->evaluate(board, depth);
    }

    double lowestSeenValue = MAX_VALUE;
    for (Move* move: board->getLegalMoves())
    {
        Board* transitionBoard = move->Execute();
        double currentValue = max(transitionBoard, depth - 1);
        if(currentValue <= lowestSeenValue)
        {
            lowestSeenValue = currentValue;
        }
        // release memory
        delete move;
        delete transitionBoard;
    }

    return lowestSeenValue;
}

double Minimax::max(const Board* board, int depth) const
{
    if(depth == 0/*|| game over*/)
    {
        return this->m_boardEvaluator->evaluate(board, depth);
    }

    double highestSeenValue = MIN_VALUE;
    for (Move* move: board->getLegalMoves())
    {
        Board* transitionBoard = move->Execute();
        double currentValue = min(transitionBoard, depth - 1);
        if(currentValue >= highestSeenValue)
        {
            highestSeenValue = currentValue;
        }
        // release memory
        delete move;
        delete transitionBoard;
    }

    return highestSeenValue;
}
