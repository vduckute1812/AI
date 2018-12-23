#include "BoardController.h"
#include "Move.h"

void BoardController::setBoard(std::vector<Tile*> board)
{
	m_board = board;
}

void BoardController::setPiece( Piece* piece )
{
	m_board.at(piece->getPosistion())->setPiece(piece);
	m_board.at(piece->getPosistion())->setOccupiedState(true);
}

void BoardController::movePiece(Move* move)
{
	int currentPosition = move->getMovePiece()->getPosistion();
	Piece* movePiece = const_cast<Piece*> (move->getMovePiece());

	m_board.at(move->getDestCoordinate())->setPiece(movePiece);
	movePiece->setPosition(move->getDestCoordinate());

	m_board.at(currentPosition)->setPiece(nullptr);
	m_board.at(currentPosition)->setOccupiedState(false);
}

void BoardController::setMoveMaker(const Alliance& alliance)
{
	m_nextMoveMaker = alliance;
}
