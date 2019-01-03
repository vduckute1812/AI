#include "whitePlayer.h"

WhitePlayer::WhitePlayer(const Board* board, const std::vector<Move*> legalMoves,
	const std::vector<Move*> opponentMoves) : Player(board, legalMoves, opponentMoves, Alliance::WHITE)
{

}

WhitePlayer::~WhitePlayer()
{

}