#include <time.h>
#include <QTextStream>
#include "Minimax.h"
#include "Move.h"
#include "Board.h"
#include "BoardEvaluator.h"
#include "StandardBoardEvaluator.h"
#include <algorithm>    // std::max

const static double MAX_VALUE = 1e4;
const static double MIN_VALUE = -1e4;

Minimax::Minimax(int searchDepth)
{
    m_boardEvaluated    = 0;
    m_quiescenceCount = 0;
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

Move* Minimax::execute(const Board* board)
{
    double currentValue;
//    int freqTableIndex = 0;

    clock_t start, end;
    start = clock();

    Move* bestMove = nullptr;
    double hightestSeenValue = MIN_VALUE;
    double lowestSeenValue = MAX_VALUE;

    QTextStream out(stdout);
    out << board->getMoveMaker() << " IS THINKING with depth " << m_searchDepth <<endl;

    CollectMove moves = board->getLegalMoves(board->getMoveMaker());

    for (Move* move: moves) {
        if(!move->isLegalMove())
        {
            delete move;
            continue;
        }
        Board* transitionBoard = move->Execute();
        m_quiescenceCount = 0;
        currentValue = transitionBoard->getMoveMaker() == Alliance::WHITE ?
                    min(transitionBoard, m_searchDepth - 1, hightestSeenValue, lowestSeenValue):
                    max(transitionBoard, m_searchDepth - 1, hightestSeenValue, lowestSeenValue);

        Board* undoBoard = move->UndoExecute();
        delete undoBoard;

        if(board->getMoveMaker() == Alliance::WHITE && currentValue > hightestSeenValue)
        {
            hightestSeenValue = currentValue;
            bestMove = move;
        }
        else if(board->getMoveMaker() == Alliance::BLACK && currentValue < lowestSeenValue)
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

double Minimax::min(const Board* board, int depth, double highest, double lowest)
{
    if(depth == 0|| isEndgame(board))
    {
        if(depth == 0)
        {
             m_boardEvaluated++;
        }
        return this->m_boardEvaluator->evaluate(board, depth);
    }

    double currentLowest = lowest;
    for (Move* move: board->getLegalMoves(board->getMoveMaker()))
    {
        Board* transitionBoard = move->Execute();
        currentLowest = std::min(currentLowest, max(transitionBoard, calculateQuiescenceDepth(move, depth), highest, currentLowest));

//        if(currentLowest <= lowestSeenValue)
//        {
//            lowestSeenValue = currentLowest;
//        }

        // release memory
        Board* undoBoard = move->UndoExecute();
        delete undoBoard;

        delete move;
        delete transitionBoard;

        if(currentLowest <= highest)
        {
            return highest;
        }
    }

    return currentLowest;
}

double Minimax::max(const Board* board, int depth, double highest, double lowest)
{
    if(depth == 0|| isEndgame(board))
    {
        if(depth == 0)
        {
            m_boardEvaluated++;
        }
        return this->m_boardEvaluator->evaluate(board, depth);
    }

    double currentHighest  = highest;
    for (Move* move: board->getLegalMoves(board->getMoveMaker()))
    {
        Board* transitionBoard = move->Execute();
        currentHighest = std::max(currentHighest, min(transitionBoard, calculateQuiescenceDepth(move, depth), currentHighest, lowest));
//        if(currentValue >= highestSeenValue)
//        {
//            highestSeenValue = currentValue;
//        }

        // release memory
        Board* undoBoard = move->UndoExecute();
        delete undoBoard;

        delete move;
        delete transitionBoard;

        if(currentHighest >= lowest)
        {
            return lowest;
        }

    }

    return currentHighest;
}

bool Minimax::isEndgame(const Board* board)
{
    return !board->hasEscapeMoves(board->getMoveMaker());
}

int Minimax::calculateQuiescenceDepth(const Move* moveTransition, int depth)
{
    if(depth == 1 && m_quiescenceCount < MAX_QUIESCENCE)
    {
//        board->isInCheck(BoardUntils::getOpponentAllianace(alliance))
        int activityMeasure = 0;
        const Board* transitionBoard = moveTransition->getTransitionBoard();
        if (transitionBoard->isInCheck(transitionBoard->getMoveMaker()))
        {
            activityMeasure += 2;
        }


//        for(const Move* move: BoardUtils.lastNMoves(moveTransition.getToBoard(), 4)) {
//            if(move.isAttack()) {
            if(moveTransition->isAttackMove()) {
                activityMeasure += 1;
            }
//        }
        if(activityMeasure > 3)
        {
            m_quiescenceCount++;
            return 2;
        }
    }
    return depth - 1;
}

