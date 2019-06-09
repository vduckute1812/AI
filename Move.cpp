#include "Move.h"
#include "Piece.h"
#include "BoardUntils.h"
#include "BoardGameWnd.h"

Move::Move( const BoardState board, const Piece* movePiece, const Piece* attackPiece, const unsigned int destCoord)
{
    m_board = board;
    m_movePiece = movePiece;
    m_attackPiece = attackPiece;
    m_destCoordinate = destCoord;
    m_movedCoordinate = movePiece->GetPosition();
    m_isFirstMove = m_movePiece->IsFirstMove();
}

unsigned int Move::GetMoveCoordinate() const
{
    return m_movedCoordinate;
}

unsigned int Move::GetDestCoordinate() const
{
    return m_destCoordinate;
}

bool Move::IsAttackMove() const
{
    const Piece* destPiece = BoardState::GetPieceOnBoard(m_board, m_destCoordinate);
    if (destPiece == nullptr)
    {
        return false;
    }
    return true;
}


BoardState Move::Execute()
{
    if(BoardGameWnd::s_tmpStateIdx >= MAX_TEMP_BOARD )
    {
        BoardState boardState;
        BoardConfig boardConfig = boardState.m_boardValue;

        BoardConfig oldBoard = m_board.m_boardValue;

        for (unsigned int idx = 0; idx < NUM_TILES_PER_COL * NUM_TILES_PER_ROW; ++idx)
        {
            boardConfig.push_back(std::make_pair(idx, oldBoard.at(idx).second));
        }
        Piece* piece = BoardState::GetPieceOnBoard(boardState, m_movedCoordinate);
        piece->SetFirstMove(false);

        boardState.SetPiece(m_movedCoordinate, nullptr);
        boardState.SetPiece(m_destCoordinate, piece);

        Alliance nextTurnPlayer = m_board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
        boardState.m_playerTurn = nextTurnPlayer;

        return boardState;
    }
    else
    {
        BoardConfig boardConfig = m_board.m_boardValue;

        Piece* piece = BoardState::GetPieceOnBoard(m_board, m_movedCoordinate);
        piece->SetFirstMove(false);

        m_board.SetPiece(m_movedCoordinate, nullptr);
        m_board.SetPiece(m_destCoordinate, piece);

        Alliance nextTurnPlayer = m_board.m_playerTurn == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
        m_board.m_playerTurn = nextTurnPlayer;
    }
    return m_board;
}

BoardState Move::UndoExecute()
{
    BoardConfig boardConfig = new BoardBuilder();
    const Board* currentBoard = m_toBoard;

    BoardConfig boardConfig = currentBoard->getBoardConfig();

    BoardConfig::iterator piecePtr;

    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        builder->setPiece(piecePtr->second);
    }

    Piece* piece = boardConfig.at(m_destCoordinate);

    if(m_isFirstMove && piece)
    {
        piece->setFirstMove(true);
    }

    builder->setPiece(m_movedCoordinate, piece);
    builder->setPiece(m_destCoordinate, const_cast<Piece*>(m_attackPiece)); // need optimize this line

    builder->setMoveMaker(currentBoard->getOpponentMaker());
    return builder->build();

}

// Use for GUI
BoardState Move::Undo()
{
//    BoardBuilder* builder = new BoardBuilder();
//    const Board* currentBoard = BoardUI::GetInstance()->GetCurrentBoard();
////    const Board* currentBoard = m_movedBoard;

//    BoardConfig boardConfig = currentBoard->getBoardConfig();

//    BoardConfig::iterator piecePtr;

//    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
//    {
//        builder->setPiece(piecePtr->second);
//    }

//    Piece* piece = boardConfig.at(m_destCoordinate);

//    if(m_isFirstMove && piece)
//    {
//        piece->setFirstMove(true);
//    }

//    builder->setPiece(m_movedCoordinate, piece);
//    builder->setPiece(m_destCoordinate, const_cast<Piece*>(m_attackPiece)); // need optimize this line

//    builder->setMoveMaker(currentBoard->getOpponentMaker());
//    return builder->build();

    BoardState test;
    return test;
}

BoardState Move::Redo()
{
//    BoardBuilder* builder = new BoardBuilder();

//    const Board* currentBoard = BoardUI::GetInstance()->GetCurrentBoard();
////    const Board* currentBoard = m_board;
//    BoardConfig boardConfig = currentBoard->getBoardConfig();

//    BoardConfig::iterator piecePtr;

//    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
//    {
//        builder->setPiece(piecePtr->second);
//    }

//    Piece* piece = boardConfig.at(m_movedCoordinate);

//    if(piece->isFirstMove())
//    {
//        piece->setFirstMove(false);
//    }

//    builder->setPiece(m_movedCoordinate, nullptr);
//    builder->setPiece(m_destCoordinate, piece); // need optimize this line

//    builder->setMoveMaker(currentBoard->getOpponentMaker());
//    return builder->build();
    BoardState test;
    return test;
}

bool Move::IsLegalMove()
{
//    Board* board = this->Execute();

//    const Board* boardUI = board;
//    BoardConfig boardConfig = boardUI->getBoardConfig();

//    bool isLegal = true;
//    int kingPosition = -1;

//    CollectPiece pieces = boardUI->getPieces(boardUI->getOpponentMaker());
//    for (const Piece* piece: pieces)
//    {
//        if(piece->getPieceType() == PieceType::KING)
//        {
//            kingPosition = piece->getPosition();
//            break;
//        }
//    }

//    CollectMove moves = boardUI->getLegalMoves(boardUI->getMoveMaker());
//    for (Move* move: moves)
//    {
//        if(move->getDestCoordinate() == kingPosition)
//        {
//            isLegal = false;
//            break;
//        }

//        delete move;
//    }

//    Board* boardUndo = this->UndoExecute();

//    delete board;
//    delete boardUndo;

//    return isLegal;
    return true;
}
