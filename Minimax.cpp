#include "Minimax.h"
#include "BoardUntils.h"
#include <QTextStream>
#include "Move.h"


const static double MAX_VALUE = 1e4;
const static double MIN_VALUE = -1e4;

void Minimax::Init()
{
    m_boardEvaluated    = 0;
    m_quiescenceCount   = 0;
    m_searchDepth       = 1;    //default value
    m_boardEvaluator    = StandardBoardEvaluator::GetInstance();
}

Move *Minimax::execute(BoardState board)
{
    double currentValue;
//    int freqTableIndex = 0;

    clock_t start, end;
    start = clock();

    Move* bestMove = nullptr;
    double hightestSeenValue = MIN_VALUE;
    double lowestSeenValue = MAX_VALUE;

    QTextStream out(stdout);
    out << QChar(board.m_playerTurn) << " IS THINKING with depth " << m_searchDepth <<endl;

    MoveCollection moves = board.GetMoveCollection(board.m_playerTurn);
//    std::sort(moves.begin(), moves.end(), [](const Move* A, const Move* B){ return BoardUntils::mvvlva(A) > BoardUntils::mvvlva(B); });
    for (Move* move: moves) {

        BoardState transitionBoard = move->Execute();
        m_quiescenceCount = 0;
        currentValue = transitionBoard.m_playerTurn == Alliance::WHITE ?
                    min(transitionBoard, m_searchDepth - 1, hightestSeenValue, lowestSeenValue):
                    max(transitionBoard, m_searchDepth - 1, hightestSeenValue, lowestSeenValue);

//        BoardState undoBoard = move->UndoExecute();

        if(board.m_playerTurn == Alliance::WHITE && currentValue > hightestSeenValue)
        {
            hightestSeenValue = currentValue;
            bestMove = move;
        }
        else if(board.m_playerTurn == Alliance::BLACK && currentValue < lowestSeenValue)
        {
            lowestSeenValue = currentValue;

            if(bestMove)
                delete bestMove;

            bestMove = move;
        }
        // release memory
        else
        {
            delete move;
        }
    }

    /* Do the work. */
    end = clock();
    m_executeTime = static_cast<double>((end-start)/ CLOCKS_PER_SEC);

    return bestMove;
}

double Minimax::min(BoardState board, u32 depth, double highest, double lowest)
{
    if(depth == 0|| IsEndgame(board))
    {
        if(depth == 0)
        {
             m_boardEvaluated++;
        }
        return this->m_boardEvaluator->evaluate(board, depth);
    }

    double currentLowest = lowest;

    MoveCollection moves = board.GetMoveCollection(board.m_playerTurn);
//    std::sort(moves.begin(), moves.end(), [](const Move* A, const Move* B){ return BoardUntils::mvvlva(A) > BoardUntils::mvvlva(B); });

    MoveCollection candidateMoves (moves.begin() , moves.begin()+4);

    for (Move* move: candidateMoves)
    {
        BoardState transitionBoard = move->Execute();
//        currentLowest = std::min(currentLowest, max(transitionBoard, calculateQuiescenceDepth(move, depth), highest, currentLowest));

        // release memory
        BoardState undoBoard = move->UndoExecute();

        delete move;

        if(currentLowest <= highest)
        {
            return highest;
        }
    }

return currentLowest;}

double Minimax::max(BoardState board, u32 depth, double highest, double lowest)
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

bool Minimax::IsEndgame(BoardState board)
{
    return false;
}

int Minimax::CalculateQuiescenceDepth(const Move *moveTransition, int depth)
{
    return 0;
}


BoardEvaluator::BoardEvaluator()
{

}

BoardEvaluator::~BoardEvaluator()
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

