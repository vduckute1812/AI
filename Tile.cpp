#include "Tile.h"

Tile::Tile(int coordinate)
{
	m_coordinate = coordinate;
}

Tile::Tile(int coordinate, Piece* piece)
{
	m_coordinate = coordinate;
	m_piece = piece;
}

Tile::~Tile()
{
	if (m_isOccupied)
	{
		delete m_piece;
	}
}

void Tile::setPiece(Piece* piece)
{
	m_piece = piece;
}

void Tile::setOccupiedState(bool isOccupied)
{
	m_isOccupied = isOccupied;
}

Piece* Tile::getPiece() const
{
	return m_piece;
}

bool Tile::isTileOccupied() const
{
	return m_isOccupied;
}

int Tile::getCoordinate()
{
	return m_coordinate;
}

bool Tile::isEmptyTile() const
{
	if (m_piece)
	{
		return false;
	}
	return true;
}
