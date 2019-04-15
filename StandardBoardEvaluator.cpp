#include "StandardBoardEvaluator.h"
#include "Board.h"
#include "Piece.h"
#include "BoardUntils.h"
#include "Move.h"

StandardBoardEvaluator::StandardBoardEvaluator()
{

}

int StandardBoardEvaluator::evaluate(const Board* board, int depth)
{
    return scorePlayer(board, Alliance::WHITE, depth) - scorePlayer(board, Alliance::BLACK, depth);
}

int StandardBoardEvaluator::scorePlayer(const Board* board, const Alliance alliance, int depth)
{
    return pieceValue(board, alliance) + mobilityRatio(board, alliance)
            + check(board, alliance) + kingThreats(board, alliance, depth) + attacks(board, alliance);
    //+....
}

int StandardBoardEvaluator::mobility(const Board* board, const Alliance alliance)
{
    return MOBILITY_MULTIPLIER * mobilityRatio(board, alliance);
}

int StandardBoardEvaluator::mobilityRatio(const Board* board, const Alliance alliance)
{
    Alliance opponentAlliance = BoardUntils::getOpponentAllianace(alliance);

    return static_cast<int>(board->getLegalMoves(alliance).size() * 100 / board->getLegalMoves(opponentAlliance).size());
}

int StandardBoardEvaluator::pieceValue(const Board *board, const Alliance alliance)
{
    int pieceValueScore = 0;
    for (const Piece* piece: board->getPieces(alliance))
    {
        pieceValueScore += piece->getPieceValue();
    }
    return pieceValueScore;
}

int StandardBoardEvaluator::check(const Board* board, const Alliance alliance)
{
    return board->isInCheck(BoardUntils::getOpponentAllianace(alliance)) ? CHECK_BONUS : 0;
}

int StandardBoardEvaluator::depthBonus(int depth)
{
    return depth == 0 ? 1 : DEPTH_BONUS * depth;
}

int StandardBoardEvaluator::kingThreats(const Board* board, const Alliance alliance, int depth)
{
    return !board->hasEscapeMoves(BoardUntils::getOpponentAllianace(alliance)) ? CHECK_MATE_BONUS * depthBonus(depth) : 0;
}

int StandardBoardEvaluator::attacks(const Board *board, const Alliance alliance)
{
    int attackScore = 0;

    for(Move* move : board->getLegalMoves(alliance))
    {
        if(move->isAttackMove())
        {
            int movePieceCoord =  move->getMoveCoordinate();
            const Piece* movedPiece = board->getPieceOnBoard(movePieceCoord);
            int attackPieceCoord = move->getDestCoordinate();
            const Piece* attackPiece = board->getPieceOnBoard(attackPieceCoord);

            if(movedPiece->getPieceValue() < attackPiece->getPieceValue())
            {
                attackScore ++;
            }
        }
    }
    return attackScore * ATTACK_MULTIPLIER;
}
