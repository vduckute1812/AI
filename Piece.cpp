#include "Piece.h"

Piece::Piece(int piecePos, Alliance pieceAlliance)
{
	m_piecePosition = piecePos;
	m_pieceAlliance = pieceAlliance;
}

Piece::~Piece()
{
}

int Piece::getPosistion() const
{
	return m_piecePosition;
}

Alliance Piece::getAlliance() const
{
	return m_pieceAlliance;
}
