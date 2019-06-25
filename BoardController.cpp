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
#include "MainWnd.h"
#include "Messenger.h"

typedef vec2<int32_t> vec2i;

BoardController::BoardController(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_modePlayer = EditModeDef::HUMAN_HUMAN;
    m_piece = nullptr;
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
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();

    Piece* piece = boardController->GetSelecetedPiece();
    Alliance currentMoveMaker = boardController->GetMoveMaker();
    if (piece && BoardUntils::IsSameAlliance(piece->GetAlliance(), currentMoveMaker))
    {
        for (Move* move : piece->calculateLegalMove(BoardGameWnd::GetInstance()->GetCurrentBoard()))
        {
            if (move->GetDestCoordinate() == coordinate)
            {
                if(move->IsLegalMove())

                {
                    ////////////////////////////////////////////////////////////////////
                    if(move->IsPromoteMove())
                    {
                        move->SetHasPromote(true);

                        PromoteWnd::GetInstance()->SetPromote(true);
                        BoardGameWnd::GetInstance()->LockTiles(false);
//                        Alliance alliance = move->GetAlliancePieceMove() == 'b' ? Alliance::BLACK : Alliance::WHITE;
//                        PromoteWnd::GetInstance()->SetPromoteAlliance(alliance);
//                        PromoteWnd::GetInstance()->AddDefaultPromotePiece();
                        PromoteWnd::GetInstance()->SetVisible(true);
                        PromoteWnd::GetInstance()->SetPromote(false);
                        BoardGameWnd::GetInstance()->LockTiles(true);
                    }

                    /////////////////////////////////////////////////////////////////////

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
    return BoardGameWnd::GetInstance()->GetCurrentBoard().playerTurn;
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

bool BoardController::IsTileOccupied(const BoardConfig &board, u32 tilePosition)
{
    return board.pieceData.at(tilePosition) != nullptr;
}

void BoardController::SetPieceOnBoard(BoardConfig &board, u32 piecePosition, Piece *piece)
{
    if(piece)
    {
        piece->SetPosition(piecePosition);
    }
    board.pieceData.at(piecePosition) = piece;
}

Piece* BoardController::GetPieceOnBoard(const BoardConfig &board, u32 piecePosition) const
{
    return board.pieceData.at(piecePosition);

}

CollectPieces BoardController::GetPiecesOnBoard(BoardConfig board, Alliance alliance) const
{
    CollectPieces pieces;
    PiecePositions::iterator piecePtr = board.pieceData.begin();
    for (;piecePtr!=board.pieceData.end();++piecePtr)
    {
        Piece* piece = *piecePtr;
        if(piece!=nullptr && BoardUntils::IsSameAlliance(piece->GetAlliance(), alliance))
        {
            pieces.push_back(piece);
        }
    }
    return pieces;
}

u32 BoardController::GetKingPosition(BoardConfig board, Alliance player) const
{
    u32 kingPosition = BoardUntils::getMaxTiles();
    PiecePositions::iterator piecePtr = board.pieceData.begin();
    for (;piecePtr!=board.pieceData.end();++piecePtr)
    {
        Piece* piece = *piecePtr;
        if(piece!=nullptr && BoardUntils::IsSameAlliance(piece->GetAlliance(), player))
        {
            if(piece->GetPieceType() == PieceType::KING)
            {
                kingPosition = piece->GetPosition();
                break;
            }
        }
    }

    return kingPosition;
}

MoveCollection BoardController::GetMoveCollections(BoardConfig board, Alliance player)
{
    MoveCollection moveCollection;
    PiecePositions::iterator piecePtr = board.pieceData.begin();
    for (; piecePtr != board.pieceData.end(); ++piecePtr)
    {
        Piece* piece = *piecePtr;
        if(piece != nullptr && BoardUntils::IsSameAlliance(piece->GetAlliance(), player))
        {
            for (Move* move: piece->calculateLegalMove(board))
            {
                moveCollection.push_back(move);
            }
        }
    }
    return moveCollection;
}
