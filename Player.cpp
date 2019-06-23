#include "Player.h"
#include "BoardGameWnd.h"

Player::Player()
{

}

Player::~Player()
{

}

BlackPlayer::~BlackPlayer()
{

}

MoveCollection BlackPlayer::GetMoveCollection(BoardConfig state)
{
    MoveCollection collection;

    return collection;
}

WhitePlayer::~WhitePlayer()
{

}

MoveCollection WhitePlayer::GetMoveCollection(BoardConfig state)
{
    MoveCollection collection;
    return collection;
}
