#include "Rook.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

const int ROOK_CANDIDATE_MOVE_COORDINATE[] = { -NUM_TILES_PER_COL,
                                               -1, 1,
                                               NUM_TILES_PER_COL };

Rook::Rook(Alliance pieceAlliance, QWidget *parent, unsigned int piecePos) :
    Piece(pieceAlliance, PieceType::ROOK, PieceValue::ROOK_VALUE, parent, piecePos)
{
}

Rook::~Rook()
{
}

bool Rook::isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(1, currentPosition) && (candidateOffset == -1);
}

bool Rook::isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL, currentPosition) && (candidateOffset == 1);
}

MoveCollection Rook::calculateLegalMove(const BoardState board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;

    for (int candidateCoordinationOffset : ROOK_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + candidateCoordinationOffset;

        while (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (   isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
                || isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
                break;
            }

            unsigned int candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            if (!BoardState::IsTileOccupied(board, candidateDestCoord) ||
            !BoardUntils::IsSameAlliance(this->GetAlliance(), BoardState::GetPieceOnBoard(board, candidateDestCoord)->GetAlliance()))
            {
                legalMoves.push_back(new Move(board, this, BoardState::GetPieceOnBoard(board, candidateDestCoord), candidateDestCoord));
            }
            else // Stop by Enemy or Alliance
            {
                break;
            }

            if (BoardState::IsTileOccupied(board, candidateDestCoord))
            {
                break;
            }

            if (candidateCoordinationOffset != NUM_TILES_PER_COL && candidateCoordinationOffset != -NUM_TILES_PER_COL)
            {
                if (BoardUntils::IsNumColumn(1, candidateDestCoord)
                    || BoardUntils::IsNumColumn(NUM_TILES_PER_COL, candidateDestCoord))
                {
                    break;
                }
            }

            candidateDestinationCoordinate += candidateCoordinationOffset;
        }
    }

	return legalMoves;
}
