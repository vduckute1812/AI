#include <time.h>
#include <QTextStream>
#include "Minimax.h"
#include "BoardUntils.h"
#include "GUI/MenuComponents/GamePlayMenu/BoardGameWnd.h"
#include "Controller/Move.h"
#include "Controller/BoardController.h"

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
    BoardGameWnd::GetInstance()->Lock(true);

    double currentValue;
//    int freqTableIndex = 0;

    clock_t start, end;
    start = clock();

    Move* bestMove = nullptr;
    double hightestSeenValue = MIN_VALUE;
    double lowestSeenValue = MAX_VALUE;

    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    MoveCollection moves = boardController->GetMoveCollections(board,board.playerTurn);
    std::sort(moves.begin(), moves.end(), [](const Move* A, const Move* B){ return BoardUntils::mvvlva(A) > BoardUntils::mvvlva(B); });

    MoveCollection candidateMoves;
    if(moves.size() < 20)
    {
        candidateMoves = moves;
    }
    else
    {
         candidateMoves = MoveCollection(moves.begin() , moves.begin()+10);
    }

    for (Move* move: candidateMoves)
    {

        BoardConfig transitionBoard = move->Execute();
        m_quiescenceCount = 0;
        currentValue = transitionBoard.playerTurn == Alliance::WHITE ?
                    min(transitionBoard, m_searchDepth - 1, hightestSeenValue, lowestSeenValue):
                    max(transitionBoard, m_searchDepth - 1, hightestSeenValue, lowestSeenValue);


        if(board.playerTurn == Alliance::WHITE && currentValue > hightestSeenValue)
        {
            hightestSeenValue = currentValue;

            bestMove = move;
            if(boardController->IsCheckMate(transitionBoard, Alliance::BLACK))
            {
                break;
            }
        }
        else if(board.playerTurn == Alliance::BLACK && currentValue < lowestSeenValue)
        {
            lowestSeenValue = currentValue;

            bestMove = move;
            if(boardController->IsCheckMate(transitionBoard, Alliance::WHITE))
            {
                break;
            }
        }

        BoardConfig undoBoard  = move->UndoExecute();
    }

    /* Do the work. */
    end = clock();
    m_executeTime = static_cast<float>((end-start)/ float(CLOCKS_PER_SEC));

    QTextStream out(stdout);
    out << QChar(board.playerTurn) << " IS THINKING with depth " << m_searchDepth << ", EXECUTED TIME: " << QString::number(m_executeTime) << endl;


    BoardGameWnd::GetInstance()->Lock(false);


    for (Move* move: moves)
    {
        if(move!=bestMove)
            delete move;
    }

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

        return m_boardEvaluator->evaluate(board, depth);
    }

    double currentLowest = lowest;

    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
//    boardController->PrintBoard(board);

    if(boardController->IsKingThreat(board, BoardUntils::OpponentPlayer(board.playerTurn)))
    {
        return m_boardEvaluator->evaluate(board, depth);
    }

    MoveCollection moves = boardController->GetMoveCollections(board,board.playerTurn);
    std::sort(moves.begin(), moves.end(), [](const Move* A, const Move* B){ return BoardUntils::mvvlva(A) > BoardUntils::mvvlva(B); });

    MoveCollection candidateMoves;
    if(moves.size() < 20)
    {
        candidateMoves = moves;
    }
    else
    {
         candidateMoves = MoveCollection(moves.begin() , moves.begin()+10);
    }

    for (Move* move: candidateMoves)
    {
        if(move->IsPromoteMove())
            continue;

        BoardConfig transitionBoard = move->Execute();
//        boardController->PrintBoard(transitionBoard);

        currentLowest = std::min(currentLowest, max(transitionBoard, /*CalculateQuiescenceDepth(move, depth)*/ depth - 1, highest, currentLowest));

        BoardConfig undoBoard = move->UndoExecute();
//        boardController->PrintBoard(undoBoard);

        if(currentLowest <= highest)
        {
            for (Move* move: moves)
            {
                // release memory
                delete move;
            }
            return highest;
        }
    }
    for (Move* move: moves)
    {
        // release memory
        delete move;
    }

    return currentLowest;
}

double Minimax::max(BoardConfig board, u32 depth, double highest, double lowest)
{
    if(depth == 0|| IsEndgame(board))
     {
         if(depth == 0)
         {
             m_boardEvaluated++;
         }
         return m_boardEvaluator->evaluate(board, depth);
     }

     double currentHighest  = highest;

     BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
//     boardController->PrintBoard(board);

     if(boardController->IsKingThreat(board, BoardUntils::OpponentPlayer(board.playerTurn)))
     {
         return m_boardEvaluator->evaluate(board, depth);
     }

     MoveCollection moves = boardController->GetMoveCollections(board,board.playerTurn);
     std::sort(moves.begin(), moves.end(), [](const Move* A, const Move* B){ return BoardUntils::mvvlva(A) > BoardUntils::mvvlva(B); });

     MoveCollection candidateMoves;
     if(moves.size() < 20)
     {
         candidateMoves = moves;
     }
     else
     {
          candidateMoves = MoveCollection(moves.begin() , moves.begin()+10);
     }

     for (Move* move: candidateMoves)
     {
         if(move->IsPromoteMove())
             continue;

         BoardConfig transitionBoard = move->Execute();
//         boardController->PrintBoard(transitionBoard);

         currentHighest = std::max(currentHighest, min(transitionBoard, /*CalculateQuiescenceDepth(move, depth)*/ depth - 1, currentHighest, lowest));

         BoardConfig undoBoard = move->UndoExecute(); // return old board
//         boardController->PrintBoard(undoBoard);

         if(currentHighest >= lowest)
         {
             for (Move* move: moves)
             {
                 // release memory
                 delete move;
             }

             return lowest;
         }
     }

     for (Move* move: moves)
     {
         // release memory
         delete move;
     }
     moves.clear();

    return currentHighest;
}


void Minimax::SetDepth(u32 depth)
{
    m_searchDepth = depth;
}

bool Minimax::SortMoveFollowValue(std::vector<Move *> moves)
{
    return false;
}

bool Minimax::IsEndgame(BoardConfig board)
{
    return false;
}

u32 Minimax::CalculateQuiescenceDepth(const Move *moveTransition, int depth)
{
    return depth - 1;
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
    return scorePlayer(board, Alliance::WHITE, depth) - scorePlayer(board, Alliance::BLACK, depth);
}

int StandardBoardEvaluator::scorePlayer(const BoardConfig board, const Alliance alliance, int depth)
{
    return pieceValue(board, alliance) + mobilityRatio(board, alliance)
        + check(board, alliance) + kingThreats(board, alliance, depth) + attacks(board, alliance);
}

int StandardBoardEvaluator::mobility(const BoardConfig board, const Alliance alliance)
{
    return MOBILITY_MULTIPLIER * mobilityRatio(board, alliance);
}

int StandardBoardEvaluator::mobilityRatio(const BoardConfig board, const Alliance alliance)
{
    Alliance opponentAlliance = alliance == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;

    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    return static_cast<int>(boardController->GetMoveCollections(board, alliance).size() * 100 / boardController->GetMoveCollections(board, opponentAlliance).size());
}

int StandardBoardEvaluator::check(const BoardConfig board, const Alliance alliance)
{
    bool isChecked = false;
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    Alliance opponentAlliance = alliance == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;

    u32 kingPosition = boardController->GetKingPosition(board, opponentAlliance);
    MoveCollection moves = boardController->GetMoveCollections(board, alliance);

    for (Move* move: moves)
    {
        if(move->GetDestCoordinate() == kingPosition)
        {
            isChecked = true;
            break;
        }
    }

    return isChecked ? CHECK_BONUS : 0;
}

int StandardBoardEvaluator::kingThreats(const BoardConfig board, const Alliance alliance, int depth)
{
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    CollectPieces pieces = boardController->GetPiecesOnBoard(board, alliance);

    MoveCollection moves = boardController->GetMoveCollections(board, alliance);

    bool hasEscapeMove = false;

    for (Move* move: moves)
    {
         if(move->IsLegalMove())
         {
             hasEscapeMove = true;
             break;
         }
    }

    return  hasEscapeMove ? CHECK_MATE_BONUS * depthBonus(depth) : check(board, alliance);
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
        Piece* piece = boardConfig.at(pieceIdx);
        if(piece)
        {
            if(BoardUntils::IsSameAlliance(piece->GetAlliance(), alliance))
            {
                pieceValueScore += piece->GetPieceValue();
            }
        }
    }
    return pieceValueScore;
}

int StandardBoardEvaluator::attacks(const BoardConfig board, const Alliance alliance)
{
    int attackScore = 0;
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();
    MoveCollection moves = boardController->GetMoveCollections(board, alliance);

    for(Move* move : moves)
    {
        if(move->IsAttackMove())
        {
            u32 movePieceCoord =  move->GetMoveCoordinate();
            const Piece* movedPiece = boardController->GetPieceOnBoard(board, movePieceCoord);
            u32 attackPieceCoord = move->GetDestCoordinate();
            const Piece* attackPiece = boardController->GetPieceOnBoard(board, attackPieceCoord);

            if(movedPiece->GetPieceValue() < attackPiece->GetPieceValue())
            {
                attackScore ++;
            }
        }
    }
    return attackScore * ATTACK_MULTIPLIER;
}

int StandardBoardEvaluator::kingSafety(const BoardConfig board, const Alliance alliance)
{
    return 0;
}

int StandardBoardEvaluator::pieceEvaluations(const BoardConfig board, const Alliance alliance)
{
    int pieceValuationScore = 0;
    int numBishops = 0;
    BoardController* boardController = BoardGameWnd::GetInstance()->GetEditModeController();

    for (const Piece* piece : boardController->GetPiecesOnBoard(board, alliance))
    {
        pieceValuationScore += piece->GetPieceValue() + piece->locationBonus();
        if(piece->GetPieceType() == PieceType::BISHOP) {
            numBishops++;
        }
    }
    return pieceValuationScore + (numBishops == 2 ? TWO_BISHOPS_BONUS : 0);
}

