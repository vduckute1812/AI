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
#include "Player.h"
#include "PieceFactory.h"

typedef vec2<int32_t> vec2i;

BoardController::BoardController(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_piece = nullptr;
    m_currentPlayer = nullptr;
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

Alliance BoardController::GetMoveMaker(const BoardConfig &board) const
{
    return board.playerTurn;
}


void BoardController::MovePiece(Move *move)
{
    if(BoardGameWnd::GetInstance()->IsLocked())
        return;

    QChar type = move->GetTypePieceMove();
    QChar alliance = move->GetAlliancePieceMove();

    ////////////////////////// Set here ////////////////////////

    QString str = "";
    if(move->IsAttackMove())
    {
        str +=  type + QString(alliance) + QString(" attack ") + move->GetTypePieceIsAttacked() + QString(" ") +QString::number(move->GetDestCoordinate());
    }
    if (move->IsPromoteMove())
    {
        str += QString(" is promoted");
    }
    if (!move->IsAttackMove() && !move->IsPromoteMove())
    {
        str += type + QString(alliance) + QString(" move to ") +QString::number(move->GetDestCoordinate());
    }

    move->SetDescription( str );

    if(move->IsPromoteMove())
    {
//        // Create promote piece
        PromoteWnd::GetInstance()->SetPromote(true);
        PromoteWnd::GetInstance()->SetPromotePiece(nullptr);
        PromoteWnd::GetInstance()->SetPromoteAlliance( move->GetMovedPiece()->GetAlliance());

        PromoteWnd::GetInstance()->exec();

        Piece* promotePiece =  PromoteWnd::GetInstance()->GetPromotePiece();
        Piece* piece = nullptr;
        if(promotePiece)
        {
            piece = PieceFactory::GeneratePiece(promotePiece->GetPieceType(), promotePiece->GetAlliance());
        }
        else
        {
            piece = PieceFactory::GeneratePiece(PieceType::BISHOP, move->GetMovedPiece()->GetAlliance());
        }

        move->SetIsPromotedPiece(piece);

    }

    MoveMgr::GetInstance()->Do(move);
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

Player *BoardController::GetCurrentPlayer()
{
    return BoardGameWnd::GetInstance()->GetCurrentPlayer();
}

