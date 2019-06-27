#include "Player.h"
#include "BoardGameWnd.h"

Player::Player()
{
    m_isAI = false;
}

Player::~Player()
{

}

void Player::SetIsAI(bool isAi)
{
    m_isAI = isAi;
}

bool Player::IsAiPlayer() const
{
    return m_isAI;
}

Alliance Player::GetAlliance() const
{
    return m_player;
}

BlackPlayer::BlackPlayer(): Player ()
{
    m_player = Alliance::BLACK;
}

BlackPlayer::~BlackPlayer()
{

}

WhitePlayer::WhitePlayer(): Player ()
{
    m_player = Alliance::WHITE;
}

WhitePlayer::~WhitePlayer()
{

}

