#include "Knight.h"
#include "Board.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

Knight::Knight(Alliance pieceAlliance, int piecePosition, QWidget *parent) : Piece(pieceAlliance, piecePosition, PieceType::KNIGHT, parent)
{
}


Knight::~Knight()
{
}

MoveCollection Knight::calculateLegalMove(const Board* board)  const
{
    MoveCollection legalMoves;

//	int candidateDestinationCoordinate;	// candidate coordinate

//	for (int currentCandidateOffset : KNIGHT_CANDIDATE_MOVE_COORDINATE)
//	{
//		candidateDestinationCoordinate = this->m_piecePosition + currentCandidateOffset;
//		if (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
//		{
//			if (isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset)
//				|| isSecondColumnExclusion(this->m_piecePosition, currentCandidateOffset)
//				|| isSeventhColumnExclusion(this->m_piecePosition, currentCandidateOffset)
//				|| isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset))
//			{
//				continue;
//			}
			
//			const Tile* candidateTile = board->getTile(candidateDestinationCoordinate);
			
//			if (!candidateTile->isTileOccupied() || !BoardUntils::isSameAlliance(this->getAlliance(), candidateTile->getPiece()->getAlliance()))
//			{
//				legalMoves.push_back(new Move(board, this, candidateDestinationCoordinate));
//			}
//		}
//	}

	return legalMoves;
}

bool Knight::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -17 || candidateOffset == -10
														|| candidateOffset ==  6  || candidateOffset ==  15 );
}

bool Knight::isSecondColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isSecondColumn(currentPosition) && (candidateOffset == -10 || candidateOffset == 6);
}

bool Knight::isSeventhColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isSeventhColumn(currentPosition) && (candidateOffset == -6 || candidateOffset == 10);
}

bool Knight::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isEighthColumn(currentPosition) && ( candidateOffset == -15 || candidateOffset == -6
														||   candidateOffset == 10  || candidateOffset == 17 );
}
