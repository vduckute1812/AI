#include "PromoteWnd.h"
#include "Tile.h"
#include "Piece.h"
#include "Defines.h"
#include "PieceFactory.h"
#include <QHBoxLayout>
#include <QWidget>

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

    QList<QString> list = {"Queen", "Knight", "Rook", "Bishop"};

    for ( u32 idx = 0; idx < NUM_TILE_PROMOTE; idx++)
    {
        Piece* pieceWhite = PieceFactory::GeneratePiece(list.at(idx), Alliance::WHITE);
        m_pieceWhite.push_back(pieceWhite);

        Piece* pieceBlack = PieceFactory::GeneratePiece(list.at(idx), Alliance::BLACK);
        m_pieceBlack.push_back(pieceBlack);
    }

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    widget->setLayout(layout);
    setWindowTitle("Promote Windows");
}

void PromoteWnd::SetPromoteAlliance(Alliance alliance)
{
    m_promoteAlliance = alliance;

    for ( u32 idx = 0; idx < NUM_TILE_PROMOTE; idx++)
    {
        Tile* tile = m_tiles[idx];
        m_promoteAlliance == Alliance::WHITE? m_pieceWhite[idx]->setParent(tile): m_pieceBlack[idx]->setParent(tile);
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
