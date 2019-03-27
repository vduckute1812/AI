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
    // If piece is available
    if(m_piece)
    {
        m_piece->setPosition(m_tileCoordinate);
    }
}

Piece* Tile::getPiece() const
{
    return m_piece;
}

const BoardTiles Tile::createEmptyTiles()
{
    BoardTiles tiles;
    for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
    {
        tiles.insert(std::pair<int, Tile*>(i, new Tile(i, nullptr)));
    }
}

Tile* Tile::GetEmptyTiles(const int idx)
{
    if(Tile::EMPTY_TILES.empty())
    {
        Tile::EMPTY_TILES = createEmptyTiles();
    }

    if(idx < BoardUntils::NUM_TILES)
    {
        return Tile::EMPTY_TILES[idx];
    }
    else
        return nullptr;
}
