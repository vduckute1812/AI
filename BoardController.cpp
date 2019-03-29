#include "BoardController.h"
#include "Board.h"
#include "Move.h"

void BoardController::setBoard( Board* board )
{
    m_board = board;
    m_currentPiece = nullptr;
}

Board* BoardController::getBoard()
{
    return m_board;
}

void BoardController::setPiece( Piece* piece )
{
    m_board->getTiles().at(piece->getPosistion())->setPiece(piece);
}

void BoardController::movePiece(Move* move)
{
    int currentPosition = move->getMovePiece()->getPosistion();
    Piece* movePieced = const_cast<Piece*> (move->getMovePiece());

    if (movePieced->getPieceType() == PieceType::PAWN)
    {
        Pawn* pawn = static_cast<Pawn*>(movePieced);
        if (pawn->isFirstMove())
        {
            pawn->setFirstMove(false);
        }
    }

    if (move->isAttack())
    {
        m_board->getTiles().at(move->getDestCoordinate())->getPiece()->diedState(true);
        m_board->getTiles().at(move->getDestCoordinate())->getPiece()->getRenderImg()->hide();

        if (m_board->getTiles().at(move->getDestCoordinate())->getPiece()->getPieceType() == PieceType::KING)
        {
            // ENDGAME
        }
    }

    m_board->getTiles().at(move->getDestCoordinate())->setPiece(movePieced);
    m_board->getTiles().at(currentPosition)->setPiece(nullptr);

    const Alliance currentMaker = BoardController::GetInstance()->getMoveMaker();
    BoardController::GetInstance()->setMoveMaker(currentMaker == Alliance::BLACK ? Alliance::WHITE : Alliance::BLACK);
}

void BoardController::setMoveMaker(const Alliance& alliance)
{
    m_nextMoveMaker = alliance;
}

void BoardController::setSelectedPiece(Piece* piece)
{
    m_currentPiece = piece;
}

Piece* BoardController::getSelectedPiece()
{
    return m_currentPiece;
}

Alliance BoardController::getMoveMaker()
{
    return m_nextMoveMaker;
}
