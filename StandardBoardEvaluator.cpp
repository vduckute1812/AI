#include "StandardBoardEvaluator.h"
#include "Board.h"
#include "Piece.h"

StandardBoardEvaluator::StandardBoardEvaluator()
{

}

int StandardBoardEvaluator::scorePlayer(const Board* board, int depth)
{
    return pieceValue(board);
    //+....
}

int StandardBoardEvaluator::pieceValue(const Board *board)
{
    int pieceValueScore = 0;
    for (const Piece* piece: board->getCurrentPieces()) {
        pieceValueScore += piece->getPieceValue();
    }
    return pieceValueScore;
}
