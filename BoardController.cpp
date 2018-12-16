#include "BoardController.h"

void BoardController::setBoard(std::vector<Tile*> board)
{
	m_board = board;
}

void BoardController::setPiece( Piece* piece )
{
	m_board.at(piece->getPosistion())->setPiece(piece);
}

void BoardController::setMovePiece(int currentPosition, int destPosition)
{
	m_board.at(destPosition)->setPiece( m_board.at(currentPosition)->getPiece() );
	m_board.at(currentPosition)->setPiece(nullptr);
}

void BoardController::setMoveMaker(const Alliance& alliance)
{
	m_nextMoveMaker = alliance;
}
