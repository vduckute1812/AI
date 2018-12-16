#pragma once
#include "Piece.h"
#include "BoardController.h"

#include <vector>

class Tile;

class Board
{
public:
	Board(BoardController*);
	~Board();

	const Tile*		getTile(int coordinate) const;
	void			printBoard() const;

private:
	void			Init();
	void			buildStandardBoard();

	Alliance				m_nextMoveMaker;
	std::vector<Tile*>		m_board;
	BoardController*		m_boardController;
};
