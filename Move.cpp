#include "Move.h"
#include "Board.h"
#include "Tile.h"
#include <assert.h>

Move::Move(const Board* board, const Piece* piece, int destinate)
{
	m_board = board;
	m_movePiece = piece;
	assert(piece);

	m_attackPiece = board->getTile(destinate)->getPiece();
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

const Piece* Move::getMovePiece() const
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

bool Move::isDone(MoveStatus status) const
{
	if (status == MoveStatus::DONE)
		return true;

	return false;
}
