#include "Piece.h"
#include "Pawn.h"

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


PieceType Piece::getPieceType() const
{
	return m_pieceType;
}

char Piece::getKeyCharacter() const
{
	return m_pieceType;
}

void Piece::hashCodeKeyValue()
{

	std::hash<char> hash_fn;

	const int prime = 31;
	int result = static_cast<int>(hash_fn(m_pieceType));

	result = prime * result + static_cast<int>(hash_fn(m_pieceAlliance));
	result = prime * result + m_piecePosition;

	if (m_pieceType == PieceType::PAWN)
	{
		Pawn* pawn = static_cast<Pawn*> (this);
		result = prime * result + (pawn->isFirstMove() ? 1: 0);
	}

	m_hashCode = result;
}


int  Piece::getHash() const
{
	return m_hashCode;
}