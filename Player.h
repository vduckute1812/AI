#pragma once
#include <vector>
#include "Piece.h"

class Move;
class Board;
class Player
{
public:
	Player(const Board* board, const std::vector<Move*> legalMoves, 
			const std::vector<Move*> opponentMoves, Alliance alliance);
	~Player();

	bool					isInCheck();
	bool					isInCheckMate();
	std::vector<Move*>		calculateActacksOnTile(int piecePosition, std::vector<Move*> moves);

private:
	const Piece*			m_King;
	std::vector<Piece*>		m_pieces;
	std::vector<Move*>		m_legalMoves;
	std::vector<Move*>		m_attackMoves;
	Alliance				m_alliance;
	bool					m_isInCheck;
};

