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

const Piece* Move::getMovePiece()
{
	return m_movePiece;
}


int Move::getDestCoordinate()
{
	return m_destCoordinate;
}

bool Move::isAttack()
{
	return m_isAttack;
}

int Move::GetHash() const
{
	const int prime = 32;
	int result = 1;
	result = result*prime + this->m_destCoordinate;
	result = result*prime + this->m_movePiece->getHash();
	return result;
}
