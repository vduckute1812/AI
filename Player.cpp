#include "Player.h"
#include "GUI/BoardGameWnd.h"
#include "Controller/BoardController.h"
#include "Minimax/Minimax.h"

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
        m_minimax = Minimax::GetInstance();
        m_minimax->Init();
        m_minimax->SetDepth(4);
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

    if( m_isAI && m_player == currentPlayer && msg.Is(msg::MOVE_DONE))
    {
        BoardGameWnd::GetInstance()->LockTiles(true);
        BoardGameWnd::GetInstance()->Lock(true);
        BoardConfig currentBoard = BoardGameWnd::GetInstance()->GetCurrentBoard();
        Move* move = m_minimax->execute(currentBoard);
        boardController->MovePiece(move);
        BoardGameWnd::GetInstance()->LockTiles(false);
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

