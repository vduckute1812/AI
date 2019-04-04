#include "Move.h"
#include "Board.h"
#include "Piece.h"
#include "BoardUntils.h"

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

int Move::getDestCoordinate()
{
    return m_destCoordinate;
}

bool Move::isAttackMove()
{
    const Piece* destPiece = m_board->getPieceOnBoard(m_destCoordinate);
    if (destPiece == nullptr)
    {
        return false;
    }
    return true;
}

void Move::Do()
{

}

void Move::Undo()
{

}
