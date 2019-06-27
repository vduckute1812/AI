#ifndef PLAYER_H
#define PLAYER_H
#include "Piece.h"

class Minimax;
class Player
{
public:
    Player();
    virtual ~Player();
    void        SetIsAI(bool isAi);
    bool        IsAiPlayer();
    Alliance    GetAlliance() const;
protected:
    Alliance    m_player;
    bool        m_isAI;  // AI player
};

class BlackPlayer: public Player
{
public:
    BlackPlayer();
    virtual ~BlackPlayer();

};

class WhitePlayer: public Player
{
public:
    WhitePlayer();
    virtual ~WhitePlayer();

};

#endif // PLAYER_H
