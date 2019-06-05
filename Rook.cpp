#include "Rook.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

Rook::Rook(Alliance pieceAlliance, QWidget *parent, int piecePos) :
    Piece(pieceAlliance, PieceType::ROOK, PieceValue::ROOK_VALUE, parent, piecePos)
{
}

Rook::~Rook()
{
}



bool Rook::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(1, currentPosition) && (candidateOffset == -1);
}

bool Rook::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL, currentPosition) && (candidateOffset == 1);
}



MoveCollection Rook::calculateLegalMove(const BoardState board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;

    for (int candidateCoordinationOffset : ROOK_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = this->m_piecePosition + candidateCoordinationOffset;

        while (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (   isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
                || isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
                break;
            }

            if (!BoardState::IsTileOccupied(board, candidateDestinationCoordinate) ||
            !BoardUntils::IsSameAlliance(this->GetAlliance(), BoardState::GetPieceOnBoard(board, candidateDestinationCoordinate)->GetAlliance()))
            {
                legalMoves.push_back(new Move(board, this, BoardState::GetPieceOnBoard(board, candidateDestinationCoordinate), candidateDestinationCoordinate));
            }
            else // Stop by Enemy or Alliance
            {
                break;
            }

            if (BoardState::IsTileOccupied(board, candidateDestinationCoordinate))
            {
                break;
            }

            if (candidateCoordinationOffset != 8 && candidateCoordinationOffset != -8)
            {
                if (BoardUntils::IsNumColumn(1, candidateDestinationCoordinate)
                    || BoardUntils::IsNumColumn(NUM_TILES_PER_COL, candidateDestinationCoordinate))
                {
                    break;
                }
            }

            candidateDestinationCoordinate += candidateCoordinationOffset;
        }
    }

	return legalMoves;
}
