#include "King.h"
#include "BoardUntils.h"
#include "GUI/MenuComponents/GamePlayMenu/Tile.h"
#include "GUI/MenuComponents/GamePlayMenu/BoardGameWnd.h"
#include "Controller/Move.h"
#include "Controller/BoardController.h"

const int KING_CANDIDATE_MOVE_COORDINATE[] = { -NUM_TILES_PER_COL-1,
                                               -NUM_TILES_PER_COL,
                                               -NUM_TILES_PER_COL+1,
                                               -1, 1,
                                                NUM_TILES_PER_COL-1,
                                                NUM_TILES_PER_COL,
                                                NUM_TILES_PER_COL+1 };


King::King(Alliance pieceAlliance, QWidget *parent, unsigned int piecePos) :
    Piece(pieceAlliance, PieceType::KING, PieceValue::KING_VALUE, parent, piecePos)
{
}


King::~King()
{
}

bool King::isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::FIRST, currentPosition) &&
            (candidateOffset == -1 || candidateOffset == -NUM_TILES_PER_COL-1 || candidateOffset == NUM_TILES_PER_COL-1);
}

bool King::isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::END_OF_COL, currentPosition) &&
            (candidateOffset == 1 || candidateOffset == -NUM_TILES_PER_COL+1 || candidateOffset == NUM_TILES_PER_COL+1);
}

MoveCollection King::calculateLegalMove(const BoardConfig board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;	// candidate coordinate

    for (int currentCandidateOffset : KING_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + currentCandidateOffset;
        if (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset))
            {
                continue;
            }
            BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
            unsigned int candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            if (!boardController->IsTileOccupied(board, candidateDestCoord) ||
            !BoardUntils::IsSameAlliance( this->GetAlliance(), boardController->GetPieceOnBoard(board, candidateDestCoord)->GetAlliance()) )
            {
                legalMoves.push_back(new Move(board, this, boardController->GetPieceOnBoard(board, candidateDestCoord), candidateDestCoord));
            }
        }
    }

	return legalMoves;
}
