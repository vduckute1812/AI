#ifndef PLAYER_H
#define PLAYER_H
#include "Piece.h"

class Player
{
public:
    Player();
    virtual ~Player();
    virtual MoveCollection GetMoveCollection(BoardState state) = 0;
protected:
    Alliance m_player;
};

class BlackPlayer: public Player
{
    virtual ~BlackPlayer();
    MoveCollection GetMoveCollection(BoardState state);
};

class WhitePlayer: public Player
{
    virtual ~WhitePlayer();
    MoveCollection GetMoveCollection(BoardState state);
};

#endif // PLAYER_H
