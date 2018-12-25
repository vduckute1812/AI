#include "Move.h"
#include "Player.h"
#include "Board.h"

Player::Player(const Board* board, const std::vector<Move*> legalMoves, 
				const std::vector<Move*> opponentMoves, Alliance alliance)
{
	m_pieces = board->calculateActivePieces(board->getTiles(), alliance);
	m_isInCheck = false;
	m_alliace = alliance;
	m_King =  board->getPieces(PieceType::KING, alliance).at(0);

	m_isInCheck = !calculateActacksOnTile(m_King->getPosistion(), opponentMoves).empty();
}

Player::~Player()
{
}

std::vector<Move*> Player::calculateActacksOnTile(int piecePosition, std::vector<Move*> moves)
{
	for (Move* move : moves)
	{
		if (piecePosition == move->getDestCoordinate())
		{
			m_attackMoves.push_back(move);
		}
	}
	return m_attackMoves;
}