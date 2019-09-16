#include "Bishop.h"
#include "BoardUntils.h"
#include "GUI/MenuComponents/Tile.h"
#include "GUI/MenuComponents/BoardGameWnd.h"
#include "Controller/Move.h"
#include "Controller/BoardController.h"

const int BISHOP_CANDIDATE_MOVE_COORDINATE[] = { -NUM_TILES_PER_COL-1,
                                                 -NUM_TILES_PER_COL+1,
                                                  NUM_TILES_PER_COL-1,
                                                  NUM_TILES_PER_COL+1 };


Bishop::Bishop(Alliance pieceAlliance, QWidget *parent, unsigned int position):
    Piece (pieceAlliance, PieceType::BISHOP, PieceValue::BISHOP_VALUE, parent, position)
{
}

Bishop::~Bishop()
{

}

bool Bishop::isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::FIRST, currentPosition) /*is first column*/
            && (candidateOffset == -NUM_TILES_PER_COL-1 || candidateOffset == NUM_TILES_PER_COL-1);
}

bool Bishop::isEightColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::END_OF_COL, currentPosition) /*is last column*/
            && (candidateOffset == -NUM_TILES_PER_COL+1 || candidateOffset == NUM_TILES_PER_COL+1);
}

MoveCollection Bishop::calculateLegalMove(const BoardConfig board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;

    for (int candidateCoordinationOffset : BISHOP_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + candidateCoordinationOffset;

        while (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
                || isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
                break;
            }

            unsigned int candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
            if (!boardController->IsTileOccupied(board, candidateDestCoord) ||
            !BoardUntils::IsSameAlliance( this->GetAlliance(), boardController->GetPieceOnBoard(board, candidateDestCoord)->GetAlliance()) )
            {
                legalMoves.push_back(new Move(board, this, boardController->GetPieceOnBoard(board, candidateDestCoord), candidateDestCoord));
            }
            else // Stop by Enemy or Alliance
            {
                break;
            }

            if (BoardUntils::IsNumColumn(1, candidateDestCoord)
                || BoardUntils::IsNumColumn(NUM_TILES_PER_COL, candidateDestCoord))
            {
                break;
            }

            if (boardController->IsTileOccupied(board, candidateDestCoord))
            {
                break;
            }

            candidateDestinationCoordinate += candidateCoordinationOffset;
        }
    }

    return legalMoves;
}

