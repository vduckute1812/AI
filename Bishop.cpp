#include "Tile.h"
#include "BoardGameWnd.h"
#include "Move.h"
#include "Bishop.h"
#include "BoardUntils.h"

Bishop::Bishop(Alliance pieceAlliance, QWidget *parent, int position):
    Piece (pieceAlliance, PieceType::BISHOP, PieceValue::BISHOP_VALUE, parent, position)
{
}

Bishop::~Bishop()
{

}

bool Bishop::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(1, currentPosition) /*is first column*/ && (candidateOffset == -9 || candidateOffset == 7);
}

bool Bishop::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL, currentPosition) /*is last column*/  && (candidateOffset == -7 || candidateOffset == 9);
}

MoveCollection Bishop::calculateLegalMove(const BoardConfig board) const
{
    MoveCollection legalMoves;

//        int candidateDestinationCoordinate;

//        for (int candidateCoordinationOffset : BISHOP_CANDIDATE_MOVE_COORDINATE)
//        {
//            candidateDestinationCoordinate = this->m_piecePosition + candidateCoordinationOffset;

//            while (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
//            {
//                if (isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
//                    || isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
//                    break;
//                }

//                if (!BoardGameWnd::IsTileOccupied(board, candidateDestinationCoordinate) ||
//                !BoardUntils::IsSameAlliance( this->GetAlliance(), BoardGameWnd::GetPieceOnBoard(board, candidateDestinationCoordinate)->GetAlliance()) )
//                {
//                    legalMoves.push_back(new Move(board, this, BoardGameWnd::GetPieceOnBoard(board, candidateDestinationCoordinate)), candidateDestinationCoordinate));
//                }
//                else // Stop by Enemy or Alliance
//                {
//                    break;
//                }

//                if (BoardUntils::isFirstColumn(candidateDestinationCoordinate)
//                    || BoardUntils::isEighthColumn(candidateDestinationCoordinate))
//                {
//                    break;
//                }

//                if (board->isTileOccupied(candidateDestinationCoordinate))
//                {
//                    break;
//                }

//                candidateDestinationCoordinate += candidateCoordinationOffset;
//            }
//        }

    return legalMoves;
}

