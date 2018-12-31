#include "Bishop.h"
#include "Move.h"
#include "Tile.h"
#include "Board.h"
#include "BoardUntils.h"


Bishop::Bishop(int piecePos, Alliance pieceAlliance, QWidget *parent) : Piece(piecePos, pieceAlliance, PieceType::BISHOP, parent)
{
}

Bishop::~Bishop()
{
}

std::vector<Move*> Bishop::calculateLegalMove(const Board* board) const
{
	std::vector<Move*> legalMoves;

	int candidateDestinationCoordinate;

	for (int candidateCoordinationOffset : BISHOP_CANDIDATE_MOVE_COORDINATE)
	{
		candidateDestinationCoordinate = this->m_piecePosition + candidateCoordinationOffset;

		while (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
		{
			if (isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
				|| isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
				break;
			}

			const Tile* candidateTile = board->getTile(candidateDestinationCoordinate);

			if (!candidateTile->isTileOccupied() || !BoardUntils::isSameAlliance( this->getAlliance(), candidateTile->getPiece()->getAlliance()) )
			{
				legalMoves.push_back(new Move(board, this, candidateDestinationCoordinate));
			}
			else // Stop by Enemy or Alliance
			{
				break;
			}

			if (BoardUntils::isFirstColumn(candidateDestinationCoordinate)
				|| BoardUntils::isEighthColumn(candidateDestinationCoordinate))
			{
				break;
			}

			if (candidateTile->isTileOccupied())
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
