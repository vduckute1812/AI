#include "Board.h"
#include "Tile.h"
#include "BoardUntils.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include <iostream>

Board::Board(BoardController* controller)
{
	Init();
	m_boardController = controller;
	m_boardController->setBoard(m_board);
	m_boardController->setMoveMaker(Alliance::WHITE);
	buildStandardBoard();
}

Board::~Board()
{
}

//Create emtpy tile board
void Board::Init()
{
	for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
	{
		m_board.push_back(new Tile(i));
	}
}

void Board::buildStandardBoard()
{
	m_boardController->GetInstance()->setPiece(  new Rook   (0 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Knight (1 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Bishop (2 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Queen  (3 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new King   (4 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Bishop (5 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Knight (6 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Rook   (7 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (8 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (9 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (10, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (11, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (12, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (13, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (14, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (15, Alliance::BLACK));

	m_boardController->GetInstance()->setPiece(  new Rook   (63, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Knight (62, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Bishop (61, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new King   (60, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Queen  (59, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Bishop (58, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Knight (57, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Rook   (56, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (55, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (54, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (53, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (52, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (51, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (50, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (49, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (48, Alliance::WHITE));

}

const Tile* Board::getTile(int coordinate) const
{
	return m_board[coordinate];
}

void Board::printBoard() const
{
	char key = 'x';
	for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
	{

		if (i % 8 == 0)
			std::cout << std::endl;

		key = m_board.at(i)->isEmptyTile() ? 'x' : m_board.at(i)->getPiece()->getKeyCharacter();
		std::cout << " " << key;
	}
	std::cout << std::endl;
}