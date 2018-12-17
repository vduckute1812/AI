#include "BoardController.h"
#include "Move.h"

void BoardController::setBoard(std::vector<Tile*> board)
{
	m_board = board;
}

void BoardController::setPiece( Piece* piece )
{
	m_board.at(piece->getPosistion())->setPiece(piece);
}

void BoardController::movePiece(Move* move)
{
	int currentPosition = move->getMovePiece()->getPosistion();
	m_board.at(move->getDestCoordinate())->setPiece(const_cast<Piece*> (move->getMovePiece()));
	m_board.at(currentPosition)->setPiece(nullptr);
}

void BoardController::setMoveMaker(const Alliance& alliance)
{
	m_nextMoveMaker = alliance;
}
