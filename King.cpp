#include "King.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

King::King(Alliance pieceAlliance, QWidget *parent, int piecePos) :
    Piece(pieceAlliance, PieceType::KING, PieceValue::KING_VALUE, parent, piecePos)
{
}


King::~King()
{
}

bool King::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(1, currentPosition) && (candidateOffset == -1 || candidateOffset == -9
		|| candidateOffset == 7);
}

bool King::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL, currentPosition) && (candidateOffset == -1 || candidateOffset == -7
		|| candidateOffset == 9);
}

MoveCollection King::calculateLegalMove(const BoardState board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;	// candidate coordinate

    for (int currentCandidateOffset : KING_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = this->m_piecePosition + currentCandidateOffset;
        if (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset))
            {
                continue;
            }

            if (!BoardState::IsTileOccupied(board, candidateDestinationCoordinate) ||
            !BoardUntils::IsSameAlliance( this->GetAlliance(), BoardState::GetPieceOnBoard(board, candidateDestinationCoordinate)->GetAlliance()) )
            {
                legalMoves.push_back(new Move(board, this, BoardState::GetPieceOnBoard(board, candidateDestinationCoordinate), candidateDestinationCoordinate));
            }
        }
    }

	return legalMoves;
}
