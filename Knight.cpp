#include "Knight.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

const int KNIGHT_CANDIDATE_MOVE_COORDINATE[] = { -2*NUM_TILES_PER_COL-1,
                                                 -2*NUM_TILES_PER_COL+1,
                                                 -NUM_TILES_PER_COL-2,
                                                 -NUM_TILES_PER_COL+2,
                                                  NUM_TILES_PER_COL-2,
                                                  NUM_TILES_PER_COL+2,
                                                  2*NUM_TILES_PER_COL-1,
                                                  2*NUM_TILES_PER_COL+1 };

Knight::Knight(Alliance pieceAlliance, QWidget *parent, unsigned int piecePosition) :
    Piece(pieceAlliance, PieceType::KNIGHT, PieceValue::KNIGHT_VALUE, parent, piecePosition)
{
}

Knight::~Knight()
{
}

bool Knight::isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(1, currentPosition)
            && (candidateOffset == -2*NUM_TILES_PER_COL-1 || candidateOffset == -NUM_TILES_PER_COL-2
             || candidateOffset == NUM_TILES_PER_COL-2 || candidateOffset == 2*NUM_TILES_PER_COL-1);
}

bool Knight::isSecondColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(2, currentPosition)
            && (candidateOffset == -NUM_TILES_PER_COL-2 || candidateOffset == NUM_TILES_PER_COL-2);
}

bool Knight::isSeventhColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL-1, currentPosition)
            && (candidateOffset == -NUM_TILES_PER_COL+2 || candidateOffset == NUM_TILES_PER_COL+2);
}

bool Knight::isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL, currentPosition)
            &&(candidateOffset == -2*NUM_TILES_PER_COL+1 || candidateOffset == -NUM_TILES_PER_COL+2
            || candidateOffset == NUM_TILES_PER_COL+2  || candidateOffset == 2*NUM_TILES_PER_COL+1);
}

MoveCollection Knight::calculateLegalMove(const BoardState board)  const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;	// candidate coordinate

    for (int currentCandidateOffset : KNIGHT_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + currentCandidateOffset;
        if (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isSecondColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isSeventhColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset))
            {
                continue;
            }

            unsigned int candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            if (!BoardState::IsTileOccupied(board, candidateDestCoord) ||
            !BoardUntils::IsSameAlliance(this->GetAlliance(), BoardState::GetPieceOnBoard(board, candidateDestCoord)->GetAlliance()))
            {
                legalMoves.push_back(new Move(board, this, BoardState::GetPieceOnBoard(board, candidateDestCoord), candidateDestCoord));
            }
        }
    }

	return legalMoves;
}

