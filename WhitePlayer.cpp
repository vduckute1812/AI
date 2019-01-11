#include "WhitePlayer.h"

WhitePlayer::WhitePlayer(const Board* board): Player(board, Alliance::WHITE)
{
}

WhitePlayer::~WhitePlayer()
{

}

std::vector<Move*> WhitePlayer::calculateKingCastles(const std::vector<Move*> playerLegals,
                                            const std::vector<Move*> opponentLegals)
{
    std::vector<Move*> nono;
    return nono;
}
