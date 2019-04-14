#include <time.h>
#include <QTextStream>
#include "Minimax.h"
#include "Move.h"
#include "Board.h"
#include "BoardEvaluator.h"
#include "StandardBoardEvaluator.h"

const static double MAX_VALUE = 1e10;
const static double MIN_VALUE = -1e10;

Minimax::Minimax(int searchDepth)
{
    m_boardEvaluated    = 0;
    m_searchDepth       = searchDepth;
    m_boardEvaluator    = new StandardBoardEvaluator();
}

Minimax::~Minimax()
{

}

int Minimax::getNumboardsEvaluated()
{
    return m_boardEvaluated;
}

Move* Minimax::execute(const Board* board, int depth)
{
    double currentValue;
//    int freqTableIndex = 0;

    clock_t start, end;
    start = clock();

    Move* bestMove = nullptr;
    double hightestSeenValue = MIN_VALUE;
    double lowestSeenValue = MAX_VALUE;

    QTextStream out(stdout);
    out << board->getMoveMaker() << " IS THINKING with depth " << depth <<endl;

    CollectMove moves = board->getLegalMoves(board->getMoveMaker());

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

double Minimax::min(const Board* board, int depth)
{
    if(depth == 0|| isEndgame(board))
    {
        if(depth == 0)
        {
             m_boardEvaluated++;
        }
        return this->m_boardEvaluator->evaluate(board, depth);
    }

    double lowestSeenValue = MAX_VALUE;
    for (Move* move: board->getLegalMoves(board->getMoveMaker()))
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

double Minimax::max(const Board* board, int depth)
{
    if(depth == 0|| isEndgame(board))
    {
        if(depth == 0)
        {
            m_boardEvaluated++;
        }
        return this->m_boardEvaluator->evaluate(board, depth);
    }

    double highestSeenValue = MIN_VALUE;
    for (Move* move: board->getLegalMoves(board->getMoveMaker()))
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

bool Minimax::isEndgame(const Board* board)
{
    return !board->hasEscapeMoves(board->getMoveMaker());
}
