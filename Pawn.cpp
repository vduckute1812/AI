#include "Pawn.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

Pawn::Pawn(Alliance pieceAlliance, QWidget *parent, int piecePos) :
    Piece(pieceAlliance, PieceType::PAWN, PieceValue::PAWN_VALUE, parent, piecePos)
{
}

Pawn::~Pawn()
{
}

bool Pawn::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(1, currentPosition) && (candidateOffset == -9 || candidateOffset == 7);
}

bool Pawn::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL, currentPosition) && (candidateOffset == -7 || candidateOffset == 9);
}

MoveCollection Pawn::calculateLegalMove(const BoardState board) const
{
    MoveCollection legalMoves;
    int candidateDestinationCoordinate;
    for (int currentCandidateOffset : PAWN_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = this->m_piecePosition + currentCandidateOffset * getDirection();

        if (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (currentCandidateOffset == 16 && this->IsFirstMove())
            {
                int candidateCoordinate = this->m_piecePosition + 8 * getDirection();
                if (BoardState::IsTileOccupied(board, candidateCoordinate))
                    continue;
            }

            if ( !BoardState::IsTileOccupied(board, candidateDestinationCoordinate) && ( currentCandidateOffset == 8								// MOVE
                                                  ||   (currentCandidateOffset == 16 && this->IsFirstMove())) )	// JUMP
            {
                legalMoves.push_back(new Move(board, this, BoardState::GetPieceOnBoard(board, candidateDestinationCoordinate), candidateDestinationCoordinate));
            }

            else if (BoardState::IsTileOccupied(board, candidateDestinationCoordinate) &&
                    (currentCandidateOffset == 7 || currentCandidateOffset == 9) &&
                    !BoardUntils::IsSameAlliance(this->GetAlliance(), BoardState::GetPieceOnBoard(board, candidateDestinationCoordinate)->GetAlliance()))
            {
                if (   isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection())
                    || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection()))
                {
                    continue;
                }

                legalMoves.push_back(new Move(board, this, BoardState::GetPieceOnBoard(board,candidateDestinationCoordinate), candidateDestinationCoordinate));
            }
        }
    }

	return legalMoves;
}


int Pawn::getDirection() const
{
    if (this->GetAlliance() == Alliance::BLACK)
	{
        return 1;
	}
	// else || Alliance::WHITE ||
    return -1;
} 
