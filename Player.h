#ifndef PLAYER_H
#define PLAYER_H
#include "Piece/Piece.h"
#include "Messenger.h"

class Minimax;
class Player: public Messenger
{
public:
    enum TypeMessage
    {
        k_msgType		= 1 << 5
    };

    Player();
    virtual ~Player() override;

    void                    SetIsAI(bool isAi);
    bool                    IsAiPlayer() const;
    Alliance                GetAlliance() const;

    virtual void            OnMessageReceived(const Message& msg) override;


protected:
    Alliance    m_player;
    bool        m_isAI;  // AI player
    Minimax*    m_minimax;
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
