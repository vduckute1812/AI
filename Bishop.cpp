#include "Bishop.h"
#include "Move.h"
#include "Tile.h"
#include "Board.h"
#include "BoardUntils.h"

Bishop::Bishop(int piecePos, Alliance pieceAlliance) : Piece(piecePos, pieceAlliance)
{
}

Bishop::~Bishop()
{
}

const std::vector<Move*> Bishop::calculateLegalMove(const Board* board) const
{
	std::vector<Move*> legalMoves;

	int candidateDestinationCoordinate;

	for (int candidateCoordinationOffset : BISHOP_CANDIDATE_MOVE_COORDINATE)
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

bool Bishop::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -9 || candidateOffset == 7);
}

bool Bishop::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isEighthColumn(currentPosition) && (candidateOffset == -7 || candidateOffset == 9);
}

char Bishop::getKeyCharacter() const
{
	return 'B';
}
