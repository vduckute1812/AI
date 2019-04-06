#include "Move.h"
#include "Board.h"
#include "Piece.h"
#include "BoardUntils.h"
#include "BoardBuilder.h"

Move::Move(const Board* board, const Piece* movePiece, const Piece* attackPiece, const int destCoord)
{
    m_board = board;
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

int Move::getDestCoordinate()
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

Board* Move::Do()
{
    BoardBuilder* builder = new BoardBuilder();

    BoardConfig boardConfig = m_board->getBoardConfig();
    BoardConfig::iterator piecePtr;

    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        builder->setPiece(piecePtr->second);
    }

    Piece* piece = boardConfig.at(m_movedCoordinate);
    piece->setFirstMove(false);

    builder->setPiece(m_movedCoordinate, nullptr);
    builder->setPiece(m_destCoordinate, piece);

    builder->setMoveMaker(m_board->getOpponentMaker());

    return builder->build();
}

Board* Move::Undo()
{
//    std::share_ptr
    BoardBuilder* builder = new BoardBuilder();

    BoardConfig boardConfig = m_board->getBoardConfig();
    BoardConfig::iterator piecePtr;

    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        builder->setPiece(piecePtr->second);
    }

    Piece* piece = boardConfig.at(m_destCoordinate);

    if(m_isFirstMove)
    {
        piece->setFirstMove(true);
    }

    builder->setPiece(m_movedCoordinate, piece);
    builder->setPiece(m_destCoordinate, const_cast<Piece*>(m_attackPiece)); // need optimize this line

    builder->setMoveMaker(m_board->getOpponentMaker());

    return builder->build();
}
