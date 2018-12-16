#include "Move.h"


Move::Move(const Board* board, const Piece* piece, const Piece* attackPiece, int destinate)
{
	m_board = board;
	m_movePiece = piece;
	m_attackPiece = attackPiece;
	m_destCoordinate = destinate;

	if (m_attackPiece)
	{
		m_isAttack = true;
	}
	else
	{
		m_isAttack = false;
	}

}


Move::~Move()
{
}
