#include "Queen.h"
#include "Tile.h"
#include "Move.h"
#include "Board.h"
#include "BoardUntils.h"

Queen::Queen(int piecePos, Alliance pieceAlliance) : Piece(piecePos, pieceAlliance, PieceType::QUEEN)
{
}


Queen::~Queen()
{
}

std::vector<Move*> Queen::calculateLegalMove(const Board* board) const
{
	std::vector<Move*> legalMoves;

	int candidateDestinationCoordinate;

	for (int candidateCoordinationOffset : QUEEN_CANDIDATE_MOVE_COORDINATE)
	{
		candidateDestinationCoordinate = this->m_piecePosition;

		while (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
		{
			if (isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
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

bool Queen::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -1 || candidateOffset == -9 
														|| candidateOffset == 7);
}

bool Queen::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isEighthColumn(currentPosition) && (candidateOffset == -1 || candidateOffset == -7 
														|| candidateOffset == 9);
}
