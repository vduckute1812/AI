#include <QMouseEvent>
#include <QTextStream>

#include "Defines.h"
#include "BoardController.h"
#include "MoveMgr.h"
#include "BoardUntils.h"
#include "Move.h"
#include "Messenger.h"
#include "Player.h"
#include "GUI/MainWnd.h"
#include "GUI/PromoteWnd.h"
#include "GUI/HistoryWnd.h"
#include "GUI/BoardGameWnd.h"
#include "GUI/DeadPieceWnd.h"
#include "Piece/Piece.h"
#include "Piece/PieceFactory.h"

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

    Piece* piece = GetSelecetedPiece();
    Alliance currentMoveMaker = GetMoveMaker();
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
    Message msg(Player::k_msgType, msg::MOVE_DONE);
    Send(msg);
}


bool BoardController::IsTileOccupied(const BoardConfig &board, u32 tilePosition) const
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

MoveCollection BoardController::GetMoveCollections(BoardConfig board, Alliance player) const
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

bool BoardController::IsKingThreat( const BoardConfig& board, Alliance player) const
{
    Alliance opponentPlayer = player == Alliance::WHITE? Alliance::BLACK : Alliance::WHITE;
    MoveCollection moves = GetMoveCollections(board, opponentPlayer);

    for (Move* move: moves)
    {
        if(move->IsAttackMove()
                && move->GetAttackedPiece()->GetPieceType() == PieceType::KING)
        {
            return true;
        }
    }

    return  false;
}

bool BoardController::IsCheckMate(const BoardConfig &board, Alliance player) const
{
    MoveCollection moves = GetMoveCollections(board, player);

    bool hasEscapeMove = false;

    for (Move* move: moves)
    {
         if(move->IsLegalMove())
         {
             hasEscapeMove = true;
             break;
         }
    }

    return !hasEscapeMove;  // don't has escape move, is check mate
}

Player *BoardController::GetCurrentPlayer()
{
    return BoardGameWnd::GetInstance()->GetCurrentPlayer();
}

void BoardController::PrintBoard(const BoardConfig &board) const
{
    QTextStream out(stdout);
    char key;
    out << "============================" <<endl;

    for (int idx = 0; idx < NUM_TILES; ++idx)
    {
        if (idx % 8 == 0)
            out << endl;

        bool isTileOccupiedIdx = IsTileOccupied(board, idx);

        Piece* piece = nullptr;
        if(isTileOccupiedIdx)
        {
            piece = GetPieceOnBoard(board, idx);
        }

        key = !isTileOccupiedIdx ? '_' :piece->GetKeyCharacter();

        if(isTileOccupiedIdx && piece->GetAlliance() == Alliance::BLACK)
            key = key + 'a' - 'A';

        out << " " << key;
    }
    out << endl;
}

