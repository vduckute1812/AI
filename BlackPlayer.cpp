#include "BlackPlayer.h"

BlackPlayer::BlackPlayer(const Board* board): Player(board, Alliance::BLACK)
{
}

BlackPlayer::~BlackPlayer()
{

}

std::vector<Move*> BlackPlayer::calculateKingCastles(const std::vector<Move*> playerLegals,
                                            const std::vector<Move*> opponentLegals)
{
    std::vector<Move*> nono;
    return nono;
}
