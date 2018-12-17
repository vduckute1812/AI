#pragma once
#include <vector>


class Move;
class Piece;
class Board;
class Player
{
public:
	Player(const Board* board, const std::vector<Move*> legalMoves);
	~Player();

private:
	std::vector<Piece*>		m_Pieces;

	std::vector<Move*>		m_legalMoves;
};

