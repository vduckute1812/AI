#include "Pawn.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

const int PAWN_CANDIDATE_MOVE_COORDINATE[] = { NUM_TILES_PER_COL-1,
                                               NUM_TILES_PER_COL,
                                               NUM_TILES_PER_COL+1,
                                               2*NUM_TILES_PER_COL };

Pawn::Pawn(Alliance pieceAlliance, QWidget *parent, unsigned int piecePos) :
    Piece(pieceAlliance, PieceType::PAWN, PieceValue::PAWN_VALUE, parent, piecePos)
{
}

Pawn::~Pawn()
{
}

bool Pawn::isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(1, currentPosition)
            && (candidateOffset == -NUM_TILES_PER_COL-1 || candidateOffset == NUM_TILES_PER_COL-1);
}

bool Pawn::isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL, currentPosition)
            && (candidateOffset == -NUM_TILES_PER_COL+1 || candidateOffset == NUM_TILES_PER_COL+1);
}

MoveCollection Pawn::calculateLegalMove(const BoardState board) const
{
    MoveCollection legalMoves;
    int candidateDestinationCoordinate;
    for (int currentCandidateOffset : PAWN_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + currentCandidateOffset * getDirection();

        if (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (currentCandidateOffset == 2*NUM_TILES_PER_COL && this->IsFirstMove())
            {
                unsigned int candidateCoordinate = this->m_piecePosition
                        + static_cast<unsigned int>(NUM_TILES_PER_COL * getDirection());
                if (BoardState::IsTileOccupied(board, candidateCoordinate))
                    continue;
            }

            unsigned int candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            if ( !BoardState::IsTileOccupied(board, candidateDestCoord)
                 && ( currentCandidateOffset  == NUM_TILES_PER_COL                              // MOVE
                 ||   (currentCandidateOffset == 2*NUM_TILES_PER_COL && this->IsFirstMove())) )	// JUMP
            {
                legalMoves.push_back(new Move(board, this, BoardState::GetPieceOnBoard(board, candidateDestCoord), candidateDestCoord));
            }
            else if (BoardState::IsTileOccupied(board, candidateDestCoord)
                 && (currentCandidateOffset == NUM_TILES_PER_COL-1 || currentCandidateOffset == NUM_TILES_PER_COL+1)
                 && !BoardUntils::IsSameAlliance(this->GetAlliance(), BoardState::GetPieceOnBoard(board, candidateDestCoord)->GetAlliance()))
            {
                if (   isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection())
                    || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection()))
                {
                    continue;
                }
                // Attack move
                legalMoves.push_back(new Move(board, this, BoardState::GetPieceOnBoard(board,candidateDestCoord), candidateDestCoord));
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
