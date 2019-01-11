#ifndef WHITEPLAYER_H
#define WHITEPLAYER_H
#include "Player.h"

class WhitePlayer :public Player
{
public:
    explicit WhitePlayer(const Board* board);
    ~WhitePlayer();
private:
    virtual std::vector<Move*> calculateKingCastles(const std::vector<Move*> playerLegals,
                                                const std::vector<Move*> opponentLegals);

};

#endif // WHITEPLAYER_H
