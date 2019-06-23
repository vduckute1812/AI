#include "Defines.h"
#include <QMouseEvent>
#include "BoardController.h"
#include "BoardGameWnd.h"
#include "Piece.h"
#include "MoveMgr.h"
#include "BoardUntils.h"
#include "Move.h"
#include "HistoryWnd.h"
#include "DeadPieceWnd.h"
#include "PromoteWnd.h"

typedef vec2<int32_t> vec2i;

BoardController::BoardController(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_modePlayer = EditModeDef::HUMAN_HUMAN;
}

void BoardController::mousePressEvent(QMouseEvent */*event*/)
{
//        vec2i pointer2D(event->x(), event->y());

}

void BoardController::SetSelecetedPiece(Piece* piece)
{
    m_piece = piece;
}

void BoardController::MoveSelectedPiece(unsigned int coordinate)
{
    if(BoardGameWnd::GetInstance()->IsLocked())
        return;
    Piece* piece = BoardController::GetInstance()->GetSelecetedPiece();
    Alliance currentMoveMaker = BoardController::GetInstance()->GetMoveMaker();
    if (piece && BoardUntils::IsSameAlliance(piece->GetAlliance(), currentMoveMaker))
    {
        for (Move* move : piece->calculateLegalMove(BoardGameWnd::GetInstance()->GetCurrentBoard()))
        {
            if (move->GetDestCoordinate() == coordinate)
            {
                if(move->IsLegalMove())
                {
                    MovePiece(move);
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


}

Alliance BoardController::GetMoveMaker()
{
    return BoardGameWnd::GetInstance()->GetCurrentBoard().m_playerTurn;
}


void BoardController::MovePiece(Move *move)
{
    if(BoardGameWnd::GetInstance()->IsLocked())
        return;

    QChar type = move->GetTypePieceMove();
    QChar alliance = move->GetAlliancePieceMove();

    ////////////////////////// Set here ////////////////////////
    if(move->IsAttackMove())
    {
        move->SetDescription( type + QString(alliance) + QString(" attack ") + move->GetTypePieceIsAttacked() + QString(" ") +QString::number(move->GetDestCoordinate()) );
    }
    else if (move->IsPromoteMove())
    {
        move->SetDescription(type + QString(alliance) + QString(" is promoted at ") + QString::number(move->GetDestCoordinate()) );
    }
    else
    {
        move->SetDescription( type + QString(alliance) + QString(" move to ") +QString::number(move->GetDestCoordinate()) );
    }

    ////////////////////////////////////////////////////////////////////
    if(move->IsPromoteMove())
    {
        move->SetHasPromote(true);

        PromoteWnd::GetInstance()->SetPromote(true);
        BoardGameWnd::GetInstance()->LockTiles(false);
        Alliance alliance = move->GetAlliancePieceMove() == 'b' ? Alliance::BLACK : Alliance::WHITE;
        PromoteWnd::GetInstance()->SetPromoteAlliance(alliance);
        PromoteWnd::GetInstance()->AddDefaultPromotePiece();
        PromoteWnd::GetInstance()->SetVisible(true);
        PromoteWnd::GetInstance()->SetPromote(false);
        BoardGameWnd::GetInstance()->LockTiles(true);
    }

    /////////////////////////////////////////////////////////////////////


    MoveMgr::GetInstance()->Do(move);
}

void BoardController::SetModePlayer(BoardController::EditModeDef modePlayer)
{
    m_modePlayer = modePlayer;
}

BoardController::EditModeDef BoardController::GetModePlayer() const
{
    return m_modePlayer;
}
