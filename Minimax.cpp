#include "Minimax.h"
#include "BoardUntils.h"


void Minimax::Init()
{

}

double Minimax::min(const Board *board, int depth, double highest, double lowest)
{
    return 0;
}

double Minimax::max(const Board *board, int depth, double highest, double lowest)
{
    return 0;
}

void Minimax::SetDepth(int depth)
{

}

bool Minimax::SortMoveFollowValue(std::vector<Move *> moves)
{
    return false;
}

bool Minimax::IsEndgame(const Board *board)
{
    return false;
}

int Minimax::CalculateQuiescenceDepth(const Move *moveTransition, int depth)
{
    return 0;
}

void BoardEvaluator::Init()
{

}

void StandardBoardEvaluator::Init()
{

}

int StandardBoardEvaluator::evaluate(const BoardState board, int depth)
{
    return 0;
}

int StandardBoardEvaluator::scorePlayer(const BoardState board, const Alliance alliance, int depth)
{
    return 0;
}

int StandardBoardEvaluator::mobility(const BoardState board, const Alliance alliance)
{
    return 0;
}

int StandardBoardEvaluator::mobilityRatio(const BoardState board, const Alliance alliance)
{
    return 0;
}

int StandardBoardEvaluator::check(const BoardState board, const Alliance alliance)
{
    return 0;
}

int StandardBoardEvaluator::kingThreats(const BoardState board, const Alliance alliance, int depth)
{
    return 0;
}

int StandardBoardEvaluator::depthBonus(int depth)
{
    return depth == 0 ? 1 : DEPTH_BONUS * depth;
}

int StandardBoardEvaluator::pieceValue(const BoardState board, const Alliance alliance)
{
    int pieceValueScore = 0;
    BoardConfig boardConfig = board.m_boardValue;
    for (unsigned int pieceIdx = 0; pieceIdx < boardConfig.size(); ++pieceIdx)
    {
        if(BoardUntils::IsSameAlliance(boardConfig.at(pieceIdx).second->GetAlliance(), alliance))
        {
            pieceValueScore += boardConfig.at(pieceIdx).second->GetPieceValue();
        }
    }
    return pieceValueScore;
}

int StandardBoardEvaluator::attacks(const BoardState board, const Alliance alliance)
{
    return 0;
}
