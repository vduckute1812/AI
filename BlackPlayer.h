#ifndef BLACKPLAYER_H
#define BLACKPLAYER_H
#include "Player.h"

class BlackPlayer: public Player
{
public:
    explicit BlackPlayer(const Board* board);
    ~BlackPlayer();

private:
    virtual std::vector<Move*> calculateKingCastles(const std::vector<Move*> playerLegals,
                                                const std::vector<Move*> opponentLegals);

};

#endif // BLACKPLAYER_H
