#include "Rook.h"
#include "Tile.h"
#include "Move.h"
#include "Board.h"
#include "BoardUntils.h"

Rook::Rook(Alliance pieceAlliance, int piecePos, QWidget *parent) : Piece(pieceAlliance, piecePos, PieceType::ROOK, parent)
{
}

Rook::~Rook()
{
}

MoveCollection Rook::calculateLegalMove(const Board* board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;

    for (int candidateCoordinationOffset : ROOK_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = this->m_piecePosition + candidateCoordinationOffset;

        while (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
        {
            if (   isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
                || isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
                break;
            }

            if (!board->isTileOccupied(candidateDestinationCoordinate) ||
            !BoardUntils::isSameAlliance(this->getAlliance(), board->getPieceOnBoard(candidateDestinationCoordinate)->getAlliance()))
            {
                legalMoves.push_back(new Move(board, this, board->getPieceOnBoard(candidateDestinationCoordinate), candidateDestinationCoordinate));
            }
            else // Stop by Enemy or Alliance
            {
                break;
            }

            if (board->isTileOccupied(candidateCoordinationOffset))
            {
                break;
            }

            if (candidateCoordinationOffset != 8 && candidateCoordinationOffset != -8)
            {
                if (BoardUntils::isFirstColumn(candidateDestinationCoordinate)
                    || BoardUntils::isEighthColumn(candidateDestinationCoordinate))
                {
                    break;
                }
            }

            candidateDestinationCoordinate += candidateCoordinationOffset;
        }
    }

	return legalMoves;
}


bool Rook::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isFirstColumn(currentPosition) && (candidateOffset == -1);
}

bool Rook::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
	return BoardUntils::isEighthColumn(currentPosition) && (candidateOffset == 1);
}

