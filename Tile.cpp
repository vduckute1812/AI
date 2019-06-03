#include "Tile.h"
#include "Piece.h"
#include "Defines.h"
#include "BoardGameWnd.h"
#include "BoardController.h"

#include <QPainter>

Tile::Tile(const int coordinate, Piece* piece, QWidget* parrent)
    : QWidget (parrent),
      m_tileCoordinate(coordinate),
      m_piece(piece)
{
    m_tileCoordinate = coordinate;
    m_piece = piece;
    resize(TILE_ROW_SIZE, TILE_COL_SIZE);
    m_defaultColor = (m_tileCoordinate + (m_tileCoordinate / NUM_TILES_PER_ROW) % 2) % 2 ? ODD_COLOR : EVEN_COLOR;
    m_currentColor = m_defaultColor;
}

void Tile::SetPiece(Piece *piece)
{
    m_piece = piece;
}

int Tile::GetCoordinate()
{
    return m_tileCoordinate;
}

bool Tile::HasPieceOnTile()
{
    return m_piece != nullptr ? true: false;
}

void Tile::setCurrentColor(QBrush color)
{
    m_currentColor = color;
}

QBrush Tile::getDefaultColor() const
{
    return m_defaultColor;
}

BoardTiles Tile::createEmptyTiles()
{
    BoardTiles tableTiles;
    Piece* NULL_PIECE = nullptr;

    for (int i = 0; i < NUM_TILES; ++i)
    {
        tableTiles.insert(std::pair<int, Tile*>(i,  new Tile(i, NULL_PIECE)));
    }

    return tableTiles;
}

Piece *Tile::GetPiece()
{
    return m_piece;
}

void Tile::mousePressEvent(QMouseEvent *event)
{
    if(BoardGameWnd::GetInstance()->IsLocked())
        return;

    BoardGameWnd::GetInstance()->GetEditModeController()->mousePressEvent(event);

//    // Make move Piece
//    int coordinate = this->GetCoordinate();

}

void Tile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(m_currentColor);
    painter.drawRect(rect());
}


