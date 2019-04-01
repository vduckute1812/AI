#include <QPainter>
#include "Tile.h"
#include "Piece.h"
#include "BoardUI.h"
#include "BoardUntils.h"

Tile::Tile(const int coordinate, Piece* piece, QWidget* parrent): QWidget (parrent)
{
    m_tileCoordinate = coordinate;
    m_piece = piece;
    resize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE);
    m_defaultColor = (m_tileCoordinate + (m_tileCoordinate / BoardUntils::NUM_TILES_PER_ROW) % 2) % 2 ? ODD_COLOR : EVEN_COLOR;
    m_currentColor = m_defaultColor;
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

void Tile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(m_currentColor);
    painter.drawRect(rect());
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
