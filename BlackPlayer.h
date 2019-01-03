#pragma once
#include "Player.h"

class BlackPlayer: public Player
{
	BlackPlayer(const Board* board, const std::vector<Move*> legalMoves,
				const std::vector<Move*> opponentMoves);
	~BlackPlayer();
};
