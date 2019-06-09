#include "Defines.h"
#include <QMouseEvent>
#include "BoardController.h"
#include "BoardGameWnd.h"
#include "Piece.h"
#include "MoveMng.h"
#include "BoardUntils.h"
#include "Move.h"

typedef vec2<int32_t> vec2i;

BoardController::BoardController(QWidget* parent /*= nullptr*/) : QWidget(parent)
{

}

void BoardController::mousePressEvent(QMouseEvent *)
{
    //    vec2i pointer2D(event->x(), event->y());
}

void BoardController::SetSelecetedPiece(Piece* piece)
{
    m_piece = piece;
}

void BoardController::MoveSelectedPiece(unsigned int coordinate)
{
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
}

Alliance BoardController::GetMoveMaker()
{
    return BoardGameWnd::GetInstance()->GetCurrentBoard().m_playerTurn;
}

void BoardController::SetMoveMaker(Alliance maker)
{
    //    BoardGameWnd::GetInstance()->GetCurrentBoard().m_playerTurn = maker;
}

void BoardController::MovePiece(Move *move)
{
    MoveMgr::GetInstance()->Do(move);
}
