#include "BoardUntils.h"
#include "BoardController.h"

void BoardController::InitGame()
{
    m_boardGame = new BoardUI();
    m_boardGame->InitBoardGame();
}

void BoardController::setBoard(Board* board)
{
    m_boardGame->SetBoard(board);
}
