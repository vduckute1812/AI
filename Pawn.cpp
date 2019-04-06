	 #include "Pawn.h"
#include "Tile.h"
#include "Move.h"
#include "Board.h"
#include "BoardUntils.h"

Pawn::Pawn(Alliance pieceAlliance, int piecePos, QWidget *parent) : Piece(pieceAlliance, piecePos, PieceType::PAWN, parent)
{
}

Pawn::~Pawn()
{
}

MoveCollection Pawn::calculateLegalMove(const Board* board) const
{
    MoveCollection legalMoves;
    int candidateDestinationCoordinate;
    for (int currentCandidateOffset : PAWN_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = this->m_piecePosition + currentCandidateOffset * getDirection();

        if (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
        {
            if (currentCandidateOffset == 16 && this->isFirstMove())
            {
                int candidateCoordinate = this->m_piecePosition + 8 * getDirection();
                if (board->isTileOccupied(candidateCoordinate))
                    continue;
            }

            if ( !board->isTileOccupied(candidateDestinationCoordinate) && ( currentCandidateOffset == 8								// MOVE
                                                  ||   (currentCandidateOffset == 16 && this->isFirstMove())) )	// JUMP
            {
                legalMoves.push_back(new Move(board, this, board->getPieceOnBoard(candidateDestinationCoordinate), candidateDestinationCoordinate));
            }

            else if (board->isTileOccupied(candidateDestinationCoordinate) &&
                    (currentCandidateOffset == 7 || currentCandidateOffset == 9) &&
                    !BoardUntils::isSameAlliance(this->getAlliance(), board->getPieceOnBoard(candidateDestinationCoordinate)->getAlliance()))
            {
                if (   isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection())
                    || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection()))
                {
                    continue;
                }

                legalMoves.push_back(new Move(board, this, board->getPieceOnBoard(candidateDestinationCoordinate), candidateDestinationCoordinate));
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

bool Pawn::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -9 || candidateOffset == 7);
}

bool Pawn::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isEighthColumn(currentPosition) && (candidateOffset == -7 || candidateOffset == 9);
}
