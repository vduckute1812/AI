#include "Tile.h"
#include "Board.h"
#include "Move.h"
#include "Bishop.h"
#include "BoardUntils.h"

Bishop::Bishop(Alliance pieceAlliance, int position, QWidget *parent):
    Piece (pieceAlliance, position, PieceType::BISHOP, PieceValue::BISHOP_VALUE, parent)
{
}

Bishop::~Bishop()
{

}

bool Bishop::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -9 || candidateOffset == 7);
}

bool Bishop::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::isEighthColumn(currentPosition) && (candidateOffset == -7 || candidateOffset == 9);
}

MoveCollection Bishop::calculateLegalMove(const Board* board) const
{
    MoveCollection legalMoves;

        int candidateDestinationCoordinate;

        for (int candidateCoordinationOffset : BISHOP_CANDIDATE_MOVE_COORDINATE)
        {
            candidateDestinationCoordinate = this->m_piecePosition + candidateCoordinationOffset;

            while (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
            {
                if (isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
                    || isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
                    break;
                }

                if (!board->isTileOccupied(candidateDestinationCoordinate) ||
                !BoardUntils::isSameAlliance( this->getAlliance(), board->getPieceOnBoard(candidateDestinationCoordinate)->getAlliance()) )
                {
                    legalMoves.push_back(new Move(board, this, board->getPieceOnBoard(candidateDestinationCoordinate), candidateDestinationCoordinate));
                }
                else // Stop by Enemy or Alliance
                {
                    break;
                }

                if (BoardUntils::isFirstColumn(candidateDestinationCoordinate)
                    || BoardUntils::isEighthColumn(candidateDestinationCoordinate))
                {
                    break;
                }

                if (board->isTileOccupied(candidateDestinationCoordinate))
                {
                    break;
                }

                candidateDestinationCoordinate += candidateCoordinationOffset;
            }
        }

    return legalMoves;
}

