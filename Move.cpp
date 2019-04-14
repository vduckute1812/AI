#include "Move.h"
#include "Board.h"
#include "Piece.h"
#include "BoardUI.h"
#include "BoardUntils.h"
#include "BoardBuilder.h"

Move::Move(const Board* board, const Piece* movePiece, const Piece* attackPiece, const int destCoord)
{
    m_board = board;
    m_toBoard = nullptr;
    m_movePiece = movePiece;
    m_attackPiece = attackPiece;
    m_destCoordinate = destCoord;
    m_movedCoordinate = movePiece->getPosition();
    m_isFirstMove = m_movePiece->isFirstMove();
}

char* Move::GetDescription()
{
    return m_description;
}

int Move::getMoveCoordinate() const
{
    return m_movedCoordinate;
}

int Move::getDestCoordinate() const
{
    return m_destCoordinate;
}

bool Move::isAttackMove()
{
    const Piece* destPiece = m_board->getPieceOnBoard(m_destCoordinate);
    if (destPiece == nullptr)
    {
        return false;
    }
    return true;
}

const Board* Move::getTransitionBoard() const
{
    return m_toBoard;
}


Board* Move::Execute()
{
    BoardBuilder* builder = new BoardBuilder();

    BoardConfig boardConfig;

    boardConfig = m_board->getBoardConfig();

    BoardConfig::iterator piecePtr;

    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        Piece* piece = piecePtr->second;
        if(piece != nullptr)
        {
            builder->setPiece(piece);
        }
    }

    Piece* piece = boardConfig.at(m_movedCoordinate);
    piece->setFirstMove(false);

    builder->setPiece(m_movedCoordinate, nullptr);
    builder->setPiece(m_destCoordinate, piece);

    builder->setMoveMaker(m_board->getOpponentMaker());
    Board* board = builder->build();
    m_toBoard = board;
    return board;
}

Board* Move::UndoExecute()
{
    BoardBuilder* builder = new BoardBuilder();
    const Board* currentBoard = m_toBoard;

    BoardConfig boardConfig = currentBoard->getBoardConfig();

    BoardConfig::iterator piecePtr;

    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        builder->setPiece(piecePtr->second);
    }

    Piece* piece = boardConfig.at(m_destCoordinate);

    if(m_isFirstMove && piece)
    {
        piece->setFirstMove(true);
    }

    builder->setPiece(m_movedCoordinate, piece);
    builder->setPiece(m_destCoordinate, const_cast<Piece*>(m_attackPiece)); // need optimize this line

    builder->setMoveMaker(currentBoard->getOpponentMaker());
    return builder->build();
}

// Use for GUI
Board* Move::Undo()
{
    BoardBuilder* builder = new BoardBuilder();
    const Board* currentBoard = BoardUI::GetInstance()->GetCurrentBoard();
//    const Board* currentBoard = m_movedBoard;

    BoardConfig boardConfig = currentBoard->getBoardConfig();

    BoardConfig::iterator piecePtr;

    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        builder->setPiece(piecePtr->second);
    }

    Piece* piece = boardConfig.at(m_destCoordinate);

    if(m_isFirstMove && piece)
    {
        piece->setFirstMove(true);
    }

    builder->setPiece(m_movedCoordinate, piece);
    builder->setPiece(m_destCoordinate, const_cast<Piece*>(m_attackPiece)); // need optimize this line

    builder->setMoveMaker(currentBoard->getOpponentMaker());
    return builder->build();
}

Board* Move::Redo()
{
    BoardBuilder* builder = new BoardBuilder();

    const Board* currentBoard = BoardUI::GetInstance()->GetCurrentBoard();
//    const Board* currentBoard = m_board;
    BoardConfig boardConfig = currentBoard->getBoardConfig();

    BoardConfig::iterator piecePtr;

    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        builder->setPiece(piecePtr->second);
    }

    Piece* piece = boardConfig.at(m_movedCoordinate);

    if(piece->isFirstMove())
    {
        piece->setFirstMove(false);
    }

    builder->setPiece(m_movedCoordinate, nullptr);
    builder->setPiece(m_destCoordinate, piece); // need optimize this line

    builder->setMoveMaker(currentBoard->getOpponentMaker());
    return builder->build();
}

bool Move::isLegalMove()
{
    Board* board = this->Execute();

    const Board* boardUI = board;
    BoardConfig boardConfig = boardUI->getBoardConfig();

    bool isLegal = true;
    int kingPosition = -1;

    CollectPiece pieces = boardUI->getPieces(boardUI->getOpponentMaker());
    for (const Piece* piece: pieces)
    {
        if(piece->getPieceType() == PieceType::KING)
        {
            kingPosition = piece->getPosition();
            break;
        }
    }

    CollectMove moves = boardUI->getLegalMoves(boardUI->getMoveMaker());
    for (Move* move: moves)
    {
        if(move->getDestCoordinate() == kingPosition)
        {
            isLegal = false;
            break;
        }

        delete move;
    }

    Board* boardUndo = this->UndoExecute();

    delete board;
    delete boardUndo;

    return isLegal;
}
