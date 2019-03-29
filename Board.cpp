#include "Piece.h"
#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "BoardBuilder.h"

Board::Board(const BoardBuilder* builder)
{
    m_boardBuilder = builder;
    setBoardConfig(builder->getBoardConfig());
}

void Board::setBoardConfig(BoardConfig tiles)
{
    BoardConfig::iterator tileNode;
    for (tileNode = tiles.begin(); tileNode != tiles.end(); ++tileNode)
    {
        m_boardConfig.insert(std::pair<int, Piece*>(tileNode->first, tileNode->second));
    }
}

Board* createStandardBoard()
{
    BoardBuilder* boardBuilder = new BoardBuilder();
    boardBuilder->setPiece(new Rook(Alliance::BLACK,   0 ));
    boardBuilder->setPiece(new Knight(Alliance::BLACK, 1 ));
    boardBuilder->setPiece(new Bishop(Alliance::BLACK, 2 ));
    boardBuilder->setPiece(new Queen(Alliance::BLACK,  3 ));
    boardBuilder->setPiece(new King(Alliance::BLACK,   4 ));
    boardBuilder->setPiece(new Bishop(Alliance::BLACK, 5 ));
    boardBuilder->setPiece(new Knight(Alliance::BLACK, 6 ));
    boardBuilder->setPiece(new Rook(Alliance::BLACK,   7 ));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   8 ));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   9 ));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   10));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   11));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   12));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   13));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   14));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   15));

    boardBuilder->setPiece(new Rook(Alliance::BLACK,   63));
    boardBuilder->setPiece(new Knight(Alliance::BLACK, 62));
    boardBuilder->setPiece(new Bishop(Alliance::BLACK, 61));
    boardBuilder->setPiece(new Queen(Alliance::BLACK,  60));
    boardBuilder->setPiece(new King(Alliance::BLACK,   59));
    boardBuilder->setPiece(new Bishop(Alliance::BLACK, 58));
    boardBuilder->setPiece(new Knight(Alliance::BLACK, 57));
    boardBuilder->setPiece(new Rook(Alliance::BLACK,   56));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   55));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   54));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   53));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   52));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   51));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   50));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   49));
    boardBuilder->setPiece(new Pawn(Alliance::BLACK,   48));

    boardBuilder->setMoveMaker(Alliance::WHITE);

    return boardBuilder->build();
}
