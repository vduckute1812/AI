#include "PromoteWnd.h"
#include "Tile.h"
#include "Defines.h"
#include <QHBoxLayout>
#include <QWidget>
#include "Piece/PieceFactory.h"

PromoteWnd::PromoteWnd(QWidget* parent): QDialog(parent)
{
    m_isPromote = false;
}

void PromoteWnd::Init()
{
    QHBoxLayout* layout = new QHBoxLayout();

    Piece* NULL_PIECE = nullptr;
    for ( u32 i = 0; i < NUM_TILE_PROMOTE; i++)
    {
        Tile* tile = new Tile(i,NULL_PIECE);
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
        m_whitePieces.push_back(pieceWhite);

        Piece* pieceBlack = PieceFactory::GeneratePiece(list.at(idx), Alliance::BLACK);
        m_blackPieces.push_back(pieceBlack);
    }

    setLayout(layout);

    setWindowTitle("Promote Windows");
}

void PromoteWnd::SetPromotePiece(Piece *piece)
{
    m_promotePiece = piece;
}

Piece *PromoteWnd::GetPromotePiece() const
{
    return m_promotePiece;
}

void PromoteWnd::SetPromoteAlliance(Alliance alliance)
{
    m_promoteAlliance = alliance;

    for ( u32 idx = 0; idx < NUM_TILE_PROMOTE; idx++)
    {
        Tile* tile = m_tiles[idx];
        m_promoteAlliance == Alliance::WHITE? tile->SetPiece(m_whitePieces[idx]): tile->SetPiece(m_blackPieces[idx]);
    }
}
void PromoteWnd::SetPromote(bool yes)
{
    m_isPromote = yes;
}

bool PromoteWnd::IsPromote() const
{
    return m_isPromote;
}

void PromoteWnd::SetVisible(bool yes)
{
    yes? show(): hide();
}

