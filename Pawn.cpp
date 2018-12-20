#include "Pawn.h"
#include "Tile.h"
#include "Move.h"
#include "Board.h"
#include "BoardUntils.h"

Pawn::Pawn(int piecePos, Alliance pieceAlliance) : Piece(piecePos, pieceAlliance, PieceType::PAWN)
{
	m_isFirstMove = true;
}


Pawn::~Pawn()
{
}

const std::vector<Move*> Pawn::calculateLegalMove(const Board* board) const
{
	std::vector<Move*> legalMoves;
	int candidateDestinationCoordinate;
	for (int currentCandidateOffset : PAWN_CANDIDATE_MOVE_COORDINATE)
	{

		candidateDestinationCoordinate = this->m_piecePosition + currentCandidateOffset * getDirection();

		if (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
		{
			const Tile* candidateTile = board->getTile(candidateDestinationCoordinate);

			if ( !candidateTile->isTileOccupied() && ( currentCandidateOffset == 8								// MOVE
												  ||   currentCandidateOffset == 16 && this->isFirstMove()) )	// JUMP
			{
				legalMoves.push_back(new Move(board, this, nullptr, candidateDestinationCoordinate));
			}

			else if ( ( currentCandidateOffset == 7 || currentCandidateOffset == 9) 
						&& this->getAlliance() != candidateTile->getPiece()->getAlliance() )
			{
				if (   isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection())
					|| isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection()))
				{
					continue;
				}

				legalMoves.push_back(new Move(board, this, candidateTile->getPiece(), candidateDestinationCoordinate));
			}
		}
	}

	return legalMoves;
}


int Pawn::getDirection() const
{
	if (this->getAlliance() == Alliance::BLACK)
	{
		return 1;
	}
	// else || Alliance::WHITE ||
	return -1;
} 

bool Pawn::isFirstMove() const
{
	return m_isFirstMove;
}

bool Pawn::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -9 || candidateOffset == 7);
}

bool Pawn::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isEighthColumn(currentPosition) && (candidateOffset == -7 || candidateOffset == 9);
}
