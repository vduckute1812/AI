#include "Knight.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"

Knight::Knight(Alliance pieceAlliance, QWidget *parent, int piecePosition) :
    Piece(pieceAlliance, PieceType::KNIGHT, PieceValue::KNIGHT_VALUE, parent, piecePosition)
{
}


Knight::~Knight()
{
}

bool Knight::isFirstColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(1, currentPosition) && (candidateOffset == -17 || candidateOffset == -10
                                                        || candidateOffset ==  6  || candidateOffset ==  15 );
}

bool Knight::isSecondColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(2, currentPosition) && (candidateOffset == -10 || candidateOffset == 6);
}

bool Knight::isSeventhColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL - 1, currentPosition) && (candidateOffset == -6 || candidateOffset == 10);
}

bool Knight::isEightColumnExclusion(int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(NUM_TILES_PER_COL - 2, currentPosition) && ( candidateOffset == -15 || candidateOffset == -6
                                                        ||   candidateOffset == 10  || candidateOffset == 17 );
}

MoveCollection Knight::calculateLegalMove(const BoardConfig board)  const
{
    MoveCollection legalMoves;

//    int candidateDestinationCoordinate;	// candidate coordinate

//    for (int currentCandidateOffset : KNIGHT_CANDIDATE_MOVE_COORDINATE)
//    {
//        candidateDestinationCoordinate = this->m_piecePosition + currentCandidateOffset;
//        if (BoardUntils::isValidTileCandidate(candidateDestinationCoordinate))
//        {
//            if (isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset)
//                || isSecondColumnExclusion(this->m_piecePosition, currentCandidateOffset)
//                || isSeventhColumnExclusion(this->m_piecePosition, currentCandidateOffset)
//                || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset))
//            {
//                continue;
//            }
			
//            if (!board->isTileOccupied(candidateDestinationCoordinate) ||
//            !BoardUntils::isSameAlliance(this->getAlliance(), board->getPieceOnBoard(candidateDestinationCoordinate)->getAlliance()))
//            {
//                legalMoves.push_back(new Move(board, this, board->getPieceOnBoard(candidateDestinationCoordinate), candidateDestinationCoordinate));
//            }
//        }
//    }

	return legalMoves;
}

