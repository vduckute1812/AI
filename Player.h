#ifndef PLAYER_H
#define PLAYER_H
#include "Piece.h"

class Player
{
public:
    Player();
    virtual ~Player();
    virtual MoveCollection GetMoveCollection(BoardConfig state) = 0;
protected:
    Alliance m_player;

};

class BlackPlayer: public Player
{
    virtual ~BlackPlayer();
    MoveCollection GetMoveCollection(BoardConfig state);
};

class WhitePlayer: public Player
{
    virtual ~WhitePlayer();
    MoveCollection GetMoveCollection(BoardConfig state);
};

#endif // PLAYER_H
