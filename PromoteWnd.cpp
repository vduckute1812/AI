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

void PromoteWnd::AddPromotePiece(Piece * piece)
{
    Piece* promotePiece = PieceFactory::GeneratePiece(piece->GetPieceType(), m_promoteAlliance);
    m_promotePieces.push_back(promotePiece);
}

void PromoteWnd::AddDefaultPromotePiece()
{
    Piece* promotePiece = PieceFactory::GeneratePiece(PieceType::QUEEN, m_promoteAlliance);
    m_promotePieces.push_back(promotePiece);
}

void PromoteWnd::DeletePromotePiece()
{
    Piece* piece = m_promotePieces.back();
    delete piece;
    m_promotePieces.pop_back();
}

Piece *PromoteWnd::GetPromotePiece() const
{
    return m_promotePieces.back();
}

void PromoteWnd::SetVisible(bool yes)
{
    yes? show(): hide();
}

