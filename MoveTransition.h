#ifndef MOVETRANSITION_H
#define MOVETRANSITION_H
#include "Move.h"

// It's used for AI implement
class Board;
class MoveTransition
{
public:
    explicit MoveTransition(const Board* fromBoard, const Board* toBoard, const Move* move, MoveStatus status);

    const Board* getFromBoard();
    const Board* getToBoard();
    const Move*  getTransitionMove();
    MoveStatus   getMoveStatus();

private:
    const Board*    m_fromBoard;
    const Board*    m_toBoard;
    const Move*     m_transitionMove;
    MoveStatus      m_moveStatus;
};

#endif // MOVETRANSITION_H
