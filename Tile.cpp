#include "Tile.h"
#include "Piece.h"
#include "BoardUI.h"
#include "BoardUntils.h"

Tile::Tile(const int coordinate, Piece* piece, QWidget* parrent): QWidget (parrent)
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

void Tile::mousePressEvent(QMouseEvent *)
{

}

namespace TILES
{
    BoardTiles createEmptyTiles()
    {
        BoardTiles tableTiles;
        Piece* NULL_PIECE = nullptr;

        for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
        {
            tableTiles.insert(std::pair<int, Tile*>(i,  new Tile(i, NULL_PIECE)));
        }

        return tableTiles;
    }
}
