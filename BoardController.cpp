#include "Board.h"
#include "BoardUntils.h"
#include "BoardController.h"
#include "MoveMgr.h"

void BoardController::InitGame()
{
    m_boardGame = new BoardUI();
    m_boardGame->InitBoardGame();
}

void BoardController::setBoard(Board* board)
{
    m_boardGame->SetBoard(board);
}

void BoardController::setMoveMaker(Alliance moveMaker)
{
    m_moveMaker = moveMaker;
}

Alliance BoardController::getMoveMaker() const
{
    return m_moveMaker;
}

void BoardController::printCurrentBoard()
{
    m_boardGame->GetCurrentBoard()->printBoard();
}

void BoardController::setSelectedPiece(Piece* piece)
{
    m_selectedPiece = piece;
}

Piece* BoardController::getSelecetedPiece() const
{
    return m_selectedPiece;
}

void BoardController::freeGame()
{
    m_boardGame->FreeTiles();
    m_boardGame->FreeInstance();
}

void BoardController::movePiece(Move* move)
{
//    MoveMgr::GetInstance()->
}
