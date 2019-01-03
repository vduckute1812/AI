#include "BlackPlayer.h"

BlackPlayer::BlackPlayer(const Board* board, const std::vector<Move*> legalMoves,
	const std::vector<Move*> opponentMoves): Player(board, legalMoves, opponentMoves, Alliance::BLACK)
{

}

BlackPlayer::~BlackPlayer()
{

}