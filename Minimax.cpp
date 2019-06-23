#include "Minimax.h"
#include "BoardUntils.h"
#include <QTextStream>
#include "Move.h"
#include "BoardGameWnd.h"
#include "BoardController.h"


const static double MAX_VALUE = 1e4;
const static double MIN_VALUE = -1e4;

void Minimax::Init()
{
    m_boardEvaluated    = 0;
    m_quiescenceCount   = 0;
    m_searchDepth       = 1;    //default value
    m_boardEvaluator    = StandardBoardEvaluator::GetInstance();
}

Move *Minimax::execute(BoardConfig board)
{
    double currentValue;
//    int freqTableIndex = 0;

    clock_t start, end;
    start = clock();

    Move* bestMove = nullptr;
    double hightestSeenValue = MIN_VALUE;
    double lowestSeenValue = MAX_VALUE;

    QTextStream out(stdout);
    out << QChar(board.playerTurn) << " IS THINKING with depth " << m_searchDepth <<endl;

    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    MoveCollection moves = boardController->GetMoveCollections(board,board.playerTurn);
//    std::sort(moves.begin(), moves.end(), [](const Move* A, const Move* B){ return BoardUntils::mvvlva(A) > BoardUntils::mvvlva(B); });
    for (Move* move: moves) {

        BoardConfig transitionBoard = move->Execute();
        m_quiescenceCount = 0;
        currentValue = transitionBoard.playerTurn == Alliance::WHITE ?
                    min(transitionBoard, m_searchDepth - 1, hightestSeenValue, lowestSeenValue):
                    max(transitionBoard, m_searchDepth - 1, hightestSeenValue, lowestSeenValue);

//        BoardState undoBoard = move->UndoExecute();

        if(board.playerTurn == Alliance::WHITE && currentValue > hightestSeenValue)
        {
            hightestSeenValue = currentValue;
            bestMove = move;
        }
        else if(board.playerTurn == Alliance::BLACK && currentValue < lowestSeenValue)
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

double Minimax::min(BoardConfig board, u32 depth, double highest, double lowest)
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

    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    MoveCollection moves = boardController->GetMoveCollections(board,board.playerTurn);
//    std::sort(moves.begin(), moves.end(), [](const Move* A, const Move* B){ return BoardUntils::mvvlva(A) > BoardUntils::mvvlva(B); });

    MoveCollection candidateMoves (moves.begin() , moves.begin()+4);

    for (Move* move: candidateMoves)
    {
        BoardConfig transitionBoard = move->Execute();
//        currentLowest = std::min(currentLowest, max(transitionBoard, calculateQuiescenceDepth(move, depth), highest, currentLowest));

        // release memory
        BoardConfig undoBoard = move->UndoExecute();

        delete move;

        if(currentLowest <= highest)
        {
            return highest;
        }
    }

return currentLowest;}

double Minimax::max(BoardConfig board, u32 depth, double highest, double lowest)
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

bool Minimax::IsEndgame(BoardConfig board)
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

int StandardBoardEvaluator::evaluate(const BoardConfig board, int depth)
{
    return 0;
}

int StandardBoardEvaluator::scorePlayer(const BoardConfig board, const Alliance alliance, int depth)
{
    return 0;
}

int StandardBoardEvaluator::mobility(const BoardConfig board, const Alliance alliance)
{
    return 0;
}

int StandardBoardEvaluator::mobilityRatio(const BoardConfig board, const Alliance alliance)
{
    return 0;
}

int StandardBoardEvaluator::check(const BoardConfig board, const Alliance alliance)
{
    return 0;
}

int StandardBoardEvaluator::kingThreats(const BoardConfig board, const Alliance alliance, int depth)
{
    return 0;
}

int StandardBoardEvaluator::depthBonus(int depth)
{
    return depth == 0 ? 1 : DEPTH_BONUS * depth;
}

int StandardBoardEvaluator::pieceValue(const BoardConfig board, const Alliance alliance)
{
    int pieceValueScore = 0;
    PiecePositions boardConfig = board.pieceData;
    for (unsigned int pieceIdx = 0; pieceIdx < boardConfig.size(); ++pieceIdx)
    {
        if(BoardUntils::IsSameAlliance(boardConfig.at(pieceIdx)->GetAlliance(), alliance))
        {
            pieceValueScore += boardConfig.at(pieceIdx)->GetPieceValue();
        }
    }
    return pieceValueScore;
}

int StandardBoardEvaluator::attacks(const BoardConfig board, const Alliance alliance)
{
    return 0;
}

