#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

class Board;

enum TypeMove
{
    MAJOR_MOVE,
    ATTACK_MOVE,
    DEFEND_MOVE, // NOT YET
    PAWN_PROMOTION,  // NOT YET
    KING_SIDE_CASTLE, // NOT YET
    QUEEN_SIDE_CASTLE, // NOT YET
    CHECK_MOVE  // NOT YET
};

class Move
{
public:
    Move(const BoardConfig board, const Piece* movePiece, const Piece* attackMove, const int destCoord);
    char*           GetDescription();

    BoardConfig          Execute();
    BoardConfig          UndoExecute();

    // Use on Board
    BoardConfig          Redo();
    BoardConfig          Undo();

    const BoardConfig    GetTransitionBoard() const;

    int                 GetMoveCoordinate() const;
    int                 GetDestCoordinate() const;
    bool                IsAttackMove() const;

    bool                IsLegalMove();

protected:
    BoardConfig   m_board;
    BoardConfig   m_toBoard;
    const Piece*        m_movePiece;
    const Piece*        m_attackPiece;

    bool            m_isFirstMove;
    int             m_movedCoordinate;
    int             m_destCoordinate;
    char            m_description[20];
};
#endif // MOVE_H
