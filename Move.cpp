#include "Move.h"
#include "Board.h"
#include "Piece.h"

Move::Move(const Board* board, const Piece* movePiece, const int destCoord)
{
    m_board = board;
    m_movePiece = movePiece;
    m_destCoordinate = destCoord;
}

MajorMove::MajorMove(const Board* board, const Piece* movePiece, const int destCoord) :Move(board, movePiece, destCoord)
{}

AttackMove::AttackMove(const Board* board, const Piece* movePiece, const int destCoord, const Piece* attackedPiece) :Move(board, movePiece, destCoord)
{
    m_attackedPiece = attackedPiece;
}
