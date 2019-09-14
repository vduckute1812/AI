#include "Player.h"
#include "GUI/BoardGameWnd.h"
#include "Controller/BoardController.h"

Player::Player()
{
    m_isAI = false;
    m_minimax = nullptr;

    ListenTo(BoardGameWnd::GetInstance()->GetEditModeController(), k_msgType, msg::MOVE_DONE);
}

Player::~Player()
{

}

void Player::SetIsAI(bool isAi)
{
    m_isAI = isAi;
    if(isAi)
    {
    }
}

bool Player::IsAiPlayer() const
{
    return m_isAI;
}

Alliance Player::GetAlliance() const
{
    return m_player;
}

void Player::OnMessageReceived(const Message &msg)
{
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    Alliance currentPlayer = boardController->GetMoveMaker();
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

