#include "Tile.h"
#include "Piece.h"
#include "BoardGameWnd.h"
#include "BoardController.h"

Tile::Tile(const int coordinate, Piece* piece, QWidget* parrent)
    : QWidget (parrent),
      m_tileCoordinate(coordinate),
      m_piece(piece)
{

}

int Tile::GetCoordinate()
{
    return m_tileCoordinate;
}

bool Tile::HasPieceOnTile()
{
    return m_piece != nullptr ? true: false;
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

    // Make move Piece
    int coordinate = this->GetCoordinate();

}
