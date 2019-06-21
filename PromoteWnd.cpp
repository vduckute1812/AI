#include "PromoteWnd.h"
#include "Tile.h"
#include "Piece.h"
#include "Defines.h"
#include "PieceFactory.h"
#include <QHBoxLayout>
#include <QWidget>

const static int NUM_TILE_PROMOTE = 4;

PromoteWnd::PromoteWnd(QWidget* parent): QMainWindow(parent)
{
}

void PromoteWnd::Init()
{
    QHBoxLayout* layout = new QHBoxLayout();

    for ( unsigned int i = 0; i < NUM_TILE_PROMOTE; i++)
    {
        Tile* tile = new Tile(i);
        tile->setFixedSize(TILE_ROW_SIZE, TILE_COL_SIZE);
        tile->SetCurrentColor(QBrush("gray"));
        tile->SetCanTouch(true);
        m_tiles.push_back(tile);
        layout->addWidget(tile);
    }

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    widget->setLayout(layout);
    setWindowTitle("Promote Windows");
}

void PromoteWnd::SetPromoteAlliance(Alliance alliance)
{
    m_promoteAlliance = alliance;
    QList<QString> list = {"Queen", "Knight", "Rook", "Bishop"};
    for ( unsigned int i = 0; i < NUM_TILE_PROMOTE; i++)
    {
        Piece* piece = PieceFactory::GeneratePiece(list.at(i), m_promoteAlliance);
        piece->setParent(m_tiles[i]);
    }

    m_isPromote = true;
}

void PromoteWnd::SetPromote(bool yes)
{
    m_isPromote = yes;
}

bool PromoteWnd::IsPromote() const
{
    return m_isPromote;
}
