#pragma once
#include <vector>
#include "Piece.h"

class Move;
class Board;
class Player
{
public:
	Player(const Board* board, const std::vector<Move*> legalMoves, Alliance alliance);
	~Player();

private:
	const Piece*			m_King;
	std::vector<Piece*>		m_Pieces;
	std::vector<Move*>		m_legalMoves;
	Alliance				m_alliace;
	bool					m_isInCheck;
};

