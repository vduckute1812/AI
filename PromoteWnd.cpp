#include "PromoteWnd.h"
#include "Tile.h"
#include "Piece.h"
#include "Defines.h"
#include "PieceFactory.h"
#include <QHBoxLayout>

PromoteWnd::PromoteWnd(QWidget* parent): QMainWindow(parent)
{
}

void PromoteWnd::Init()
{
    QHBoxLayout* layout = new QHBoxLayout();

    QList<QString> list = {"Queen", "Knight", "Rook", "Bishop"};
    for ( int i = 0; i < 4; i++)
    {
        Piece* piece = PieceFactory::GeneratePiece(list.at(i), m_promoteAlliance);
        Tile* tile = new Tile(i, piece);
        piece->setParent(tile);
        tile->setFixedSize(TILE_ROW_SIZE, TILE_COL_SIZE);
        tile->SetCurrentColor(QBrush("white"));
        m_tiles.push_back(tile);
        layout->addWidget(tile);
    }

    setLayout(layout);
}

void PromoteWnd::SetPromoteAlliance(Alliance alliance)
{
    m_promoteAlliance = alliance;
}
