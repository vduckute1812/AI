#include "Queen.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"
#include "BoardGameWnd.h"
#include "BoardController.h"

const static int QUEEN_CANDIDATE_MOVE_COORDINATE[] = { -NUM_TILES_PER_COL-1,
                                                       -NUM_TILES_PER_COL,
                                                       -NUM_TILES_PER_COL+1,
                                                       -1, 1,
                                                       NUM_TILES_PER_COL-1,
                                                       NUM_TILES_PER_COL,
                                                       NUM_TILES_PER_COL+1 };

Queen::Queen(Alliance pieceAlliance, QWidget *parent, unsigned int piecePos) :
    Piece(pieceAlliance, PieceType::QUEEN, PieceValue::QUEEN_VALUE, parent, piecePos)
{
}

Queen::~Queen()
{
}

bool Queen::isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::FIRST, currentPosition)
            && (candidateOffset == -1 || candidateOffset == -NUM_TILES_PER_COL-1 || candidateOffset == NUM_TILES_PER_COL-1);
}

bool Queen::isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::END_OF_COL, currentPosition)
            && (candidateOffset == 1 || candidateOffset == -NUM_TILES_PER_COL+1 || candidateOffset == NUM_TILES_PER_COL+1);
}

MoveCollection Queen::calculateLegalMove(const BoardConfig board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;

    for (int candidateCoordinationOffset : QUEEN_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + candidateCoordinationOffset;

        while (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
                || isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
                break;
            }

            BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();

            unsigned int candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            if (!boardController->IsTileOccupied(board, candidateDestCoord) ||
            !BoardUntils::IsSameAlliance(this->GetAlliance(), boardController->GetPieceOnBoard(board, candidateDestCoord)->GetAlliance()))
            {
                legalMoves.push_back(new Move(board, this, boardController->GetPieceOnBoard(board, candidateDestCoord), candidateDestCoord));
            }
            else // Stop by Enemy or Alliance
            {
                break;
            }

            if (boardController->IsTileOccupied(board, candidateDestCoord))
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
