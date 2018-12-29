#include "BoardController.h"
#include "Move.h"
#include "Board.h"
#include "Tile.h"


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
	Piece* movePiece = const_cast<Piece*> (move->getMovePiece());

	m_board->getTiles().at(move->getDestCoordinate())->setPiece(movePiece);
	m_board->getTiles().at(currentPosition)->setPiece(nullptr);
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