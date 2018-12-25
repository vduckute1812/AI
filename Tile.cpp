#include "Tile.h"
#include "Piece.h"
#include <QPainter>
#include "BoardUntils.h"

Tile::Tile(int coordinate, QWidget* parent) :QWidget(parent)
{
	m_coordinate = coordinate;
	m_isOccupied = false;
	(coordinate + (coordinate / BoardUntils::NUM_TILES_PER_ROW) % 2) % 2 ? setStyleSheet("background-color:rgb(200,0,0);") : setStyleSheet("background-color:rgb(0,100,0);");
	resize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE);
}

Tile::Tile(int coordinate, Piece* piece, QWidget* parent) : QWidget(parent)
{
	m_coordinate = coordinate;
	m_piece = piece;
	m_isOccupied = true;
	(coordinate + (coordinate / BoardUntils::NUM_TILES_PER_ROW) % 2) % 2 ? setStyleSheet("background-color:rgb(100,0,0);") : setStyleSheet("background-color:rgb(0,100,0);");
	resize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE);
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
	if (piece)
	{
		piece->setParent(this);
		piece->setPosition(m_coordinate);

		m_isOccupied = true;
	}
	else
	{
		m_isOccupied = false;
	}
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
