#include "Tile.h"
#include "Piece.h"
#include "Defines.h"
#include "BoardGameWnd.h"
#include "BoardController.h"
#include "BoardUntils.h"
#include "Move.h"

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

void Tile::SetCurrentColor(QBrush color)
{
    m_currentColor = color;
}

QBrush Tile::GetDefaultColor() const
{
    return m_defaultColor;
}

BoardTiles Tile::createEmptyTiles()
{
    BoardTiles tableTiles;
    Piece* NULL_PIECE = nullptr;

    for (int i = 0; i < NUM_TILES; ++i)
    {
        tableTiles.push_back(new Tile(i, NULL_PIECE));
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


    if(BoardGameWnd::GetInstance()->IsLocked())
        return;

    // Make move Piece
    int coordinate = this->GetCoordinate();
    Piece* piece = BoardController::GetInstance()->GetSelecetedPiece();
    Alliance currentMoveMaker = BoardController::GetInstance()->GetMoveMaker();
    if (piece  && BoardUntils::IsSameAlliance(piece->GetAlliance(), currentMoveMaker))
    {
        for (Move* move : piece->calculateLegalMove(BoardGameWnd::GetInstance()->GetCurrentBoard()))
        {
            if (move->GetDestCoordinate() == coordinate)
            {
                if(move->IsLegalMove())
                {
                    BoardController::GetInstance()->MovePiece(move);
                }
                else
                {
                    delete move;
                }
            }
            else
            {
                delete move;
            }
        }
    }

    BoardController::GetInstance()->SetSelecetedPiece(this->GetPiece());

    // Set colors on Board. Render posible move
    BoardGameWnd::GetInstance()->ResetColorTiles();
    Piece* pieceColor = BoardController::GetInstance()->GetSelecetedPiece();

    if (pieceColor  && BoardUntils::IsSameAlliance(pieceColor->GetAlliance(), BoardController::GetInstance()->GetMoveMaker()))
    {
        this->SetCurrentColor(CHOOSE_COLOR);
        for (Move* move : pieceColor->calculateLegalMove(BoardGameWnd::GetInstance()->GetCurrentBoard()))
        {
            unsigned int destCoordinate = move->GetDestCoordinate();
            Tile* tile = BoardGameWnd::GetInstance()->GetTiles().at(destCoordinate);
            if(move->IsLegalMove())
            {
                if(move->IsAttackMove())
                {
                    tile->SetCurrentColor(ATTACK_COLOR);
                }
                else {
                    tile->SetCurrentColor(MOVE_COLOR);
                }
            }
            delete move;
        }
    }
}

void Tile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(m_currentColor);
    painter.drawRect(rect());
}


