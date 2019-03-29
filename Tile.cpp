#include "Tile.h"
#include "Piece.h"
#include "BoardUntils.h"

Tile::Tile(const int coordinate, Piece* piece)
{
    m_tileCoordinate = coordinate;
    m_piece = piece;
}

Tile::~Tile()
{

}

int Tile::getCoordinate() const
{
    return m_tileCoordinate;
}

bool Tile::isTileOccupied() const
{
    if(m_piece == nullptr)
        return false;
    else
        return true;
}

void Tile::setPiece(Piece *piece)
{
    m_piece = piece;

    if(m_piece)
    {
        m_piece->setPosition(m_tileCoordinate);
    }
}

Piece* Tile::getPiece() const
{
    return m_piece;
}
