#pragma once
#include "Player.h"

class WhitePlayer : public Player
{
	WhitePlayer(const Board* board, const std::vector<Move*> legalMoves,
		const std::vector<Move*> opponentMoves);
	~WhitePlayer();
};
