#include "Move.h"
#include "Piece.h"
#include "BoardUntils.h"
#include "BoardGameWnd.h"
#include "PromoteWnd.h"
#include "BoardController.h"

Move::Move( const BoardConfig board, const Piece* movePiece, const Piece* attackPiece, const unsigned int destCoord)
{
    m_board = board;
    m_movePiece = movePiece;
    m_attackPiece = attackPiece;
    m_destCoordinate = destCoord;
    m_movedCoordinate = movePiece->GetPosition();
    m_isFirstMove = m_movePiece->IsFirstMove();
    m_killedPiece = nullptr;
    m_promotePiece = nullptr;
    m_isPromotePiece = false;
    m_description = "";
}

unsigned int Move::GetMoveCoordinate() const
{
    return m_movedCoordinate;
}

unsigned int Move::GetDestCoordinate() const
{
    return m_destCoordinate;
}

const Piece *Move::GetMovedPiece() const
{
    return m_movePiece;
}

const Piece *Move::GetAttackedPiece() const
{
    return m_attackPiece;
}

bool Move::IsAttackMove() const
{
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    const Piece* destPiece = boardController->GetPieceOnBoard(m_board, m_destCoordinate);
    if (destPiece == nullptr)
    {
        return false;
    }
    return true;
}

BoardConfig Move::Execute()
{
//    if(BoardGameWnd::s_tmpStateIdx >= MAX_TEMP_BOARD )
//    {
//        BoardState boardState;
//        BoardConfig boardConfig = boardState.m_boardValue;

//        BoardConfig oldBoard = m_board.m_boardValue;

//        for (unsigned int idx = 0; idx < NUM_TILES_PER_COL * NUM_TILES_PER_ROW; ++idx)
//        {
//            boardConfig.push_back(std::make_pair(idx, oldBoard.at(idx).second));
//        }
//        Piece* piece = BoardState::GetPieceOnBoard(boardState, m_movedCoordinate);
//        piece->SetFirstMove(false);
//        m_killedPiece = BoardState::GetPieceOnBoard(boardState, m_destCoordinate);

//        boardState.SetPiece(m_movedCoordinate, nullptr);
//        boardState.SetPiece(m_destCoordinate, piece);

//        Alliance nextTurnPlayer = m_board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
//        boardState.m_playerTurn = nextTurnPlayer;

//        return boardState;
//    }
//    else
//    {
        BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
        Piece* piece = boardController->GetPieceOnBoard(m_board, m_movedCoordinate);
        piece->SetFirstMove(false);
        m_killedPiece = boardController->GetPieceOnBoard(m_board, m_destCoordinate);

//        if(m_isPromotePiece)
//        {
//            PromoteWnd::GetInstance()->SetPromoteAlliance(m_movePiece->GetAlliance());
//            PromoteWnd::GetInstance()->AddDefaultPromotePiece();

//            m_promotePiece = piece;
//            piece = PromoteWnd::GetInstance()->GetPromotePiece();
//        }

        boardController->SetPieceOnBoard(m_board, m_movedCoordinate, nullptr);
        boardController->SetPieceOnBoard(m_board, m_destCoordinate, piece);

        Alliance nextTurnPlayer = m_board.playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
        m_board.playerTurn = nextTurnPlayer;
//    }


    return m_board;
}

BoardConfig Move::UndoExecute()
{
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    Piece* piece = boardController->GetPieceOnBoard(m_board, m_destCoordinate);

//    if(m_isPromotePiece)
//    {
//        piece = m_promotePiece;
//        boardController->SetPieceOnBoard(m_board, m_movedCoordinate, m_promotePiece);
//        PromoteWnd::GetInstance()->DeletePromotePiece();
//    }
//    else
//    {
        boardController->SetPieceOnBoard(m_board, m_movedCoordinate, piece);
//    }

    boardController->SetPieceOnBoard(m_board,m_destCoordinate, m_killedPiece);
    m_killedPiece = nullptr;

    if(m_isFirstMove && piece)
    {
        piece->SetFirstMove(true);
    }

    Alliance nextTurnPlayer = m_board.playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
    m_board.playerTurn = nextTurnPlayer;

    return m_board;
}

// Use for GUI
BoardConfig Move::Undo()
{
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();

    Piece* piece = boardController->GetPieceOnBoard(m_board, m_destCoordinate);

//    if(m_isPromotePiece)
//    {
//        piece = m_promotePiece;
//        boardController->SetPieceOnBoard(m_board,m_destCoordinate, nullptr);
//        boardController->SetPieceOnBoard(m_board,m_movedCoordinate, m_promotePiece);
//        PromoteWnd::GetInstance()->DeletePromotePiece();
//    }
//    else
//    {
        boardController->SetPieceOnBoard(m_board,m_movedCoordinate, piece);
//    }

    boardController->SetPieceOnBoard(m_board,m_destCoordinate, m_killedPiece);
    m_killedPiece = nullptr;

    if(m_isFirstMove && piece)
        piece->SetFirstMove(true);

    Alliance nextTurnPlayer = m_board.playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
    m_board.playerTurn = nextTurnPlayer;

    return m_board;
}

BoardConfig Move::Redo()
{
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();

    Piece* piece = boardController->GetPieceOnBoard(m_board, m_movedCoordinate);
    piece->SetFirstMove(false);
    m_killedPiece = boardController->GetPieceOnBoard(m_board, m_destCoordinate);

//    if(m_isPromotePiece)
//    {
//        PromoteWnd::GetInstance()->SetPromoteAlliance(m_movePiece->GetAlliance());
//        PromoteWnd::GetInstance()->AddDefaultPromotePiece();
//        piece = PromoteWnd::GetInstance()->GetPromotePiece();
//    }

    boardController->SetPieceOnBoard(m_board,m_movedCoordinate, nullptr);
    boardController->SetPieceOnBoard(m_board,m_destCoordinate, piece);

    Alliance nextTurnPlayer = m_board.playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
    m_board.playerTurn = nextTurnPlayer;

    return m_board;
}

bool Move::IsLegalMove()
{
    BoardConfig board = this->Execute();
    bool isLegal = true;

    // Get Opponent moves
    Alliance opponentPlayer = board.playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;

    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();

    unsigned int kingPosition = boardController->GetKingPosition(board,opponentPlayer);
    MoveCollection moves = boardController->GetMoveCollections(board, board.playerTurn);
    for (Move* move: moves)
    {
        if(move->GetDestCoordinate() == kingPosition)
        {
            isLegal = false;

            delete move;
            break;
        }
        delete move;
    }
    this->Undo();
    return isLegal;
}


bool Move::IsPromoteMove()
{
    if(m_movePiece->GetPieceType() == PieceType::PAWN)
    {
        for ( unsigned int i = 0; i < NUM_TILES_PER_COL; ++i)
        {
            if(m_movePiece->GetAlliance() == Alliance::WHITE && m_destCoordinate == i)
            {
                return true;
            }
            else if(m_movePiece->GetAlliance() == Alliance::BLACK && m_destCoordinate == NUM_TILES - i)
            {
                return true;
            }
        }
    }
    return false;
}

void Move::SetDescription(const QString &desc)
{
    m_description = desc;
}

const QString &Move::GetDescription() const
{
    return m_description;
}

void Move::SetHasPromote(bool yes)
{
    m_isPromotePiece = yes;
}

QChar Move::GetAlliancePieceMove() const
{
    return m_movePiece->GetAlliance();
}

QChar Move::GetAlliancePieceAttack() const
{
    if(IsAttackMove())
    {
        return m_attackPiece->GetAlliance();
    }
    else
        return QChar();}

QChar Move::GetTypePieceMove() const
{
    return m_movePiece->GetPieceType();
}

QChar Move::GetTypePieceIsAttacked() const
{
    if(IsAttackMove())
    {
        return m_attackPiece->GetPieceType();
    }
    else
        return QChar();
}
