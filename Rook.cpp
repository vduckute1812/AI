#include "Rook.h"
#include "Tile.h"
#include "Move.h"
#include "Board.h"
#include "BoardUntils.h"

Rook::Rook(int piecePos, Alliance pieceAlliance, QWidget *parent) : Piece(piecePos, pieceAlliance, PieceType::ROOK, parent)
{
}

Rook::~Rook()
{
}

std::vector<Move*> Rook::calculateLegalMove(const Board* board) const
{
	std::vector<Move*> legalMoves;

	int candidateDestinationCoordinate;

	for (int candidateCoordinationOffset : ROOK_CANDIDATE_MOVE_COORDINATE)
	{
		candidateDestinationCoordinate = this->m_piecePosition;

		while (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
		{
			if (   isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
				|| isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
				break;
			}

			const Tile* candidateTile = board->getTile(candidateDestinationCoordinate);

			if (!candidateTile->isTileOccupied())
			{
				legalMoves.push_back(new Move(board, this, nullptr, candidateDestinationCoordinate));
			}
			else if (this->getAlliance() != candidateTile->getPiece()->getAlliance())
			{
				legalMoves.push_back(new Move(board, this, candidateTile->getPiece(), candidateDestinationCoordinate));
			}
			else // Stop by Enemy or Alliance
			{
				break;
			}

			candidateDestinationCoordinate += candidateCoordinationOffset;
		}
	}

	return legalMoves;
}


bool Rook::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -1);
}

bool Rook::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isEighthColumn(currentPosition) && (candidateOffset == 1);
}

