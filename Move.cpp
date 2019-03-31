#include "Move.h"
#include "Board.h"
#include "Piece.h"

Move::Move(const Board* board, const Piece* movePiece, const int destCoord)
{
    m_board = board;
    m_movePiece = movePiece;
    m_destCoordinate = destCoord;
}

char* Move::GetDescription()
{
    return m_description;
}

void Move::Do()
{

}

void Move::Undo()
{

}
