#include "Player.h"
#include "Board.h"

Player::Player(const Board* board, const std::vector<Move*> legalMoves)
{
	m_Pieces = board->calculateActivePieces(board->getTiles(), Alliance::WHITE);

}


Player::~Player()
{
}
