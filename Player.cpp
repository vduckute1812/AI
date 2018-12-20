#include "Player.h"
#include "Board.h"

Player::Player(const Board* board, const std::vector<Move*> legalMoves, Alliance alliance)
{
	m_Pieces = board->calculateActivePieces(board->getTiles(), alliance);
	m_isInCheck = false;
	m_alliace = alliance;
	m_King =  board->getPieces(PieceType::KING, alliance).at(0);
}

Player::~Player()
{
}
