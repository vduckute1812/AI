#include "Piece.h"
#include "Board.h"
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

void BoardController::printCurrentBoard()
{
    m_boardGame->GetCurrentBoard()->printBoard();
}

void BoardController::freeGame()
{
    m_boardGame->FreeTiles();
    m_boardGame->FreeInstance();
}
