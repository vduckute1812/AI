#include "Tile.h"
#include "Piece.h"
#include "Defines.h"
#include "BoardGameWnd.h"
#include "BoardController.h"
#include "BoardUntils.h"
#include "PromoteWnd.h"
#include "Move.h"

#include <QPainter>

Tile::Tile(unsigned int coordinate, Piece* piece, QWidget* parrent)
    : QWidget (parrent),
      m_tileCoordinate(coordinate),
      m_piece(piece)
{
    m_piece = piece;
    resize(TILE_ROW_SIZE, TILE_COL_SIZE);
    m_defaultColor = (m_tileCoordinate + (m_tileCoordinate / NUM_TILES_PER_ROW) % 2) % 2 ? ODD_COLOR : EVEN_COLOR;
    m_currentColor = m_defaultColor;
    m_canTouch = false;

//    connect(this, &Tile::promotePiece, PromoteWnd::GetInstance(), &PromoteWnd);
}

void Tile::SetPiece(Piece *piece)
{
    if(m_piece != nullptr)
    {
        m_piece->SetVisible(false);
    }

    m_piece = piece;
    if(piece != nullptr)
    {
//        m_piece->SetVisible(false);
        m_piece->SetPosition(m_tileCoordinate);
        m_piece->setParent(this);
        m_piece->SetVisible(true, this);
    }
    ListenTo(BoardGameWnd::GetInstance());
}

unsigned int Tile::GetCoordinate()
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

Piece *Tile::GetPiece()
{
    return m_piece;
}

void Tile::mousePressEvent(QMouseEvent *event)
{
    if(BoardGameWnd::GetInstance()->IsLocked() || !m_canTouch)
        return;

//    if(PromoteWnd::GetInstance()->IsPromote())
//    {
//        Piece* piece = this->GetPiece();
////        emit(promotePiece(piece));
//        PromoteWnd::GetInstance()->AddPromotePiece(piece);
//        PromoteWnd::GetInstance()->SetPromote(false);

//        BoardGameWnd::GetInstance()->LockTiles(true);
//        PromoteWnd::GetInstance()->SetVisible(false);
//        return;
//    }

    BoardGameWnd::GetInstance()->GetEditModeController()->mousePressEvent(event);

    // Make move Piece
    unsigned int coordinate = this->GetCoordinate();
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();

    boardController->MoveSelectedPiece(coordinate);
    boardController->SetSelecetedPiece(this->GetPiece());

    // Set colors on Board. Render posible move
    BoardGameWnd::GetInstance()->ResetColorTiles();
    Piece* pieceColor = boardController->GetSelecetedPiece();

    if (pieceColor  && BoardUntils::IsSameAlliance(pieceColor->GetAlliance(), boardController->GetMoveMaker()))
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
                else
                {
                    tile->SetCurrentColor(MOVE_COLOR);
                }
            }
            delete move;
        }
    }
    Message msg(BoardGameWnd::k_msgType, msg::BOARD_CHANGED);
    Send(msg);
}

void Tile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(m_currentColor);
    painter.drawRect(rect());
}

void Tile::SetCanTouch(bool yes)
{
    m_canTouch = yes;
}

bool Tile::CanTouch() const
{
    return m_canTouch;
}
