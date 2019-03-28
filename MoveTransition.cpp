#include "MoveTransition.h"

MoveTransition::MoveTransition(const Board* fromBoard, const Board* toBoard, const Move* move, MoveStatus status)
{
    m_fromBoard = fromBoard;
    m_toBoard = toBoard;
    m_transitionMove = move;
    m_moveStatus = status;
}

const Board* MoveTransition::getFromBoard()
{
    return m_fromBoard;
}

const Board* MoveTransition::getToBoard()
{
    return m_toBoard;
}

const Move*  MoveTransition::getTransitionMove()
{
    return m_transitionMove;
}

MoveStatus   MoveTransition::getMoveStatus()
{
    return m_moveStatus;
}
