#include "King.h"
#include "Board.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

King::King(Alliance pieceAlliance, int piecePos, QWidget *parent) :Piece(pieceAlliance, piecePos, PieceType::KING, parent)
{
}


King::~King()
{
}

bool King::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -1 || candidateOffset == -9
		|| candidateOffset == 7);
}

bool King::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isEighthColumn(currentPosition) && (candidateOffset == -1 || candidateOffset == -7
		|| candidateOffset == 9);
}

MoveCollection King::calculateLegalMove(const Board* board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;	// candidate coordinate

    for (int currentCandidateOffset : KING_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = this->m_piecePosition + currentCandidateOffset;
        if (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset))
            {
                continue;
            }

            if (!board->isTileOccupied(candidateDestinationCoordinate) ||
            !BoardUntils::isSameAlliance( this->getAlliance(), board->getPieceOnBoard(candidateDestinationCoordinate)->getAlliance()) )
            {
                legalMoves.push_back(new Move(board, this, board->getPieceOnBoard(candidateDestinationCoordinate), candidateDestinationCoordinate));
            }
        }
    }

	return legalMoves;
}
