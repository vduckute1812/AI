#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

class Board;

enum TypeMove
{
    MAJOR_MOVE,
    ATTACK_MOVE,
    DEFEND_MOVE,        // NOT YET
    PAWN_PROMOTION,     // NOT YET
    KING_SIDE_CASTLE,   // NOT YET
    QUEEN_SIDE_CASTLE,  // NOT YET
    CHECK_MOVE          // NOT YET
};

class Move
{
public:
    Move(const BoardState board, const Piece* movePiece, const Piece* attackPiece, const unsigned int destCoord);

    BoardState          Execute();
    BoardState          UndoExecute();

    // Use on Board
    BoardState          Redo();
    BoardState          Undo();

    unsigned int        GetMoveCoordinate() const;
    unsigned int        GetDestCoordinate() const;
    bool                IsAttackMove() const;

    bool                IsLegalMove();

protected:
    BoardState          m_board;
    const Piece*        m_movePiece;
    const Piece*        m_attackPiece;

    bool                m_isFirstMove;
    unsigned int        m_movedCoordinate;
    unsigned int        m_destCoordinate;
};
#endif // MOVE_H
