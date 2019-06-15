#include "Move.h"
#include "Piece.h"
#include "BoardUntils.h"
#include "BoardGameWnd.h"

Move::Move( const BoardState board, const Piece* movePiece, const Piece* attackPiece, const unsigned int destCoord)
{
    m_board = board;
    m_movePiece = movePiece;
    m_attackPiece = attackPiece;
    m_destCoordinate = destCoord;
    m_movedCoordinate = movePiece->GetPosition();
    m_isFirstMove = m_movePiece->IsFirstMove();
    m_killedPiece = nullptr;
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

bool Move::IsAttackMove() const
{
    const Piece* destPiece = BoardState::GetPieceOnBoard(m_board, m_destCoordinate);
    if (destPiece == nullptr)
    {
        return false;
    }
    return true;
}


BoardState Move::Execute()
{
    if(BoardGameWnd::s_tmpStateIdx >= MAX_TEMP_BOARD )
    {
        BoardState boardState;
        BoardConfig boardConfig = boardState.m_boardValue;

        BoardConfig oldBoard = m_board.m_boardValue;

        for (unsigned int idx = 0; idx < NUM_TILES_PER_COL * NUM_TILES_PER_ROW; ++idx)
        {
            boardConfig.push_back(std::make_pair(idx, oldBoard.at(idx).second));
        }
        Piece* piece = BoardState::GetPieceOnBoard(boardState, m_movedCoordinate);
        piece->SetFirstMove(false);
        m_killedPiece = BoardState::GetPieceOnBoard(boardState, m_destCoordinate);

        boardState.SetPiece(m_movedCoordinate, nullptr);
        boardState.SetPiece(m_destCoordinate, piece);

        Alliance nextTurnPlayer = m_board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
        boardState.m_playerTurn = nextTurnPlayer;

        return boardState;
    }
    else
    {
        Piece* piece = BoardState::GetPieceOnBoard(m_board, m_movedCoordinate);
        piece->SetFirstMove(false);
        m_killedPiece = BoardState::GetPieceOnBoard(m_board, m_destCoordinate);

        m_board.SetPiece(m_movedCoordinate, nullptr);
        m_board.SetPiece(m_destCoordinate, piece);

        Alliance nextTurnPlayer = m_board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
        m_board.m_playerTurn = nextTurnPlayer;
    }
    return m_board;
}

BoardState Move::UndoExecute()
{
    Piece* piece = BoardState::GetPieceOnBoard(m_board, m_destCoordinate);
    m_board.SetPiece(m_movedCoordinate, piece);
    m_board.SetPiece(m_destCoordinate, m_killedPiece);
    m_killedPiece = nullptr;

    if(m_isFirstMove && piece)
    {
        piece->SetFirstMove(true);
    }

    Alliance nextTurnPlayer = m_board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
    m_board.m_playerTurn = nextTurnPlayer;

    return m_board;
}

// Use for GUI
BoardState Move::Undo()
{
    Piece* piece = BoardState::GetPieceOnBoard(m_board, m_destCoordinate);
    m_board.SetPiece(m_movedCoordinate, piece);
    m_board.SetPiece(m_destCoordinate, m_killedPiece);
    m_killedPiece = nullptr;

    if(m_isFirstMove && piece)
        piece->SetFirstMove(true);

    Alliance nextTurnPlayer = m_board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
    m_board.m_playerTurn = nextTurnPlayer;

    return m_board;
}

BoardState Move::Redo()
{
    Piece* piece = BoardState::GetPieceOnBoard(m_board, m_movedCoordinate);
    piece->SetFirstMove(false);
    m_killedPiece = BoardState::GetPieceOnBoard(m_board, m_destCoordinate);

    m_board.SetPiece(m_movedCoordinate, nullptr);
    m_board.SetPiece(m_destCoordinate, piece);

    Alliance nextTurnPlayer = m_board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
    m_board.m_playerTurn = nextTurnPlayer;

    return m_board;
}

bool Move::IsLegalMove()
{
    BoardState board = this->Execute();
    bool isLegal = true;

    // Get Opponent moves
    Alliance opponentPlayer = board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;

    unsigned int kingPosition = board.GetKingPosition(opponentPlayer);
    MoveCollection moves = board.GetMoveCollection(board.m_playerTurn);
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

void Move::SetDescription(const QString &desc)
{
    m_description = desc;
}

const QString &Move::GetDescription() const
{
    return m_description;
}

QChar Move::GetAlliancePieceMove() const
{
    return m_movePiece->GetAlliance();
}

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
