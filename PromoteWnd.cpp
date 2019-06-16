#include "PromoteWnd.h"
#include "Tile.h"
#include "Piece.h"
#include "Defines.h"
#include <QHBoxLayout>

PromoteWnd::PromoteWnd(QWidget* parent): QWidget(parent)
{

}

void PromoteWnd::Init()
{
    QHBoxLayout* layout = new QHBoxLayout();

    Piece* NULL_PIECE = nullptr;
    for ( int i = 0; i < 4; i++)
    {
        Tile* tile = new Tile(i,NULL_PIECE);
        tile->setFixedSize(TILE_ROW_SIZE, TILE_COL_SIZE);
        tile->SetCurrentColor(QBrush("white"));
        layout->addWidget(tile);
        m_tiles.push_back(tile);
    }

    setLayout(layout);
}
