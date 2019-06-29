#include "Player.h"
#include "BoardGameWnd.h"
#include "BoardController.h"
#include "Minimax.h"

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
    if( m_isAI && msg.Is(msg::MOVE_DONE))
    {
        BoardGameWnd::GetInstance()->Lock(true);
        BoardConfig currentBoard = BoardGameWnd::GetInstance()->GetCurrentBoard();
        Move* move = m_minimax->execute(currentBoard);
        boardController->MovePiece(move);
        BoardGameWnd::GetInstance()->Lock(false);
    }
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

