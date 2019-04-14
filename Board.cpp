#include <QTextStream>
#include "Board.h"

// Piece data
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Move.h"
#include "Piece.h"

#include "BoardUntils.h"
#include "BoardBuilder.h"

Board::Board(const BoardBuilder* builder)
{
    m_boardBuilder = builder;
}

Board::~Board()
{
    delete m_boardBuilder;
}

Alliance Board::getMoveMaker() const
{
    return m_boardBuilder->getMoveMaker();
}

Alliance Board::getOpponentMaker() const
{
    Alliance current = m_boardBuilder->getMoveMaker();
    return current == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;
}

CollectPiece Board::getPieces(const Alliance alliance) const
{
    CollectPiece pieces;

    for (int idx = 0; idx < BoardUntils::NUM_TILES; ++idx)
    {
        if(isTileOccupied(idx))
        {
            const Piece* piece = getPieceOnBoard(idx);
            if(BoardUntils::isSameAlliance(piece->getAlliance(), alliance))
            {
                pieces.push_back(piece);
            }
        }
    }
    return pieces;
}

const BoardConfig Board::getBoardConfig() const
{
    return m_boardBuilder->getBoardConfig();
}

CollectMove Board::getLegalMoves(const Alliance alliance) const
{
    CollectMove moves;
    CollectPiece pieces = getPieces(alliance);

    for (const Piece* piece: pieces)
    {
        CollectMove subMoves = piece->calculateLegalMove(this);
        for (Move* move: subMoves)
        {
            moves.push_back(move);
        }
    }
    return moves;
}

const Piece* Board::getPieceOnBoard(int index) const
{
    if(index < 0 || index >= BoardUntils::NUM_TILES)
        return nullptr;

    if(!isTileOccupied(index))
        return nullptr;

    Piece* piece = m_boardBuilder->getBoardConfig().at(index);

    return piece;
}

bool Board::isTileOccupied(const int idx) const
{
    if(idx < 0 && idx >= BoardUntils::NUM_TILES)
        return false;

    BoardConfig boardConfig = m_boardBuilder->getBoardConfig();

    Piece* piece = boardConfig.at(idx);
    if(piece == nullptr)
        return false;
    return true;
}

void Board::printBoard() const
{
    QTextStream out(stdout);
    char key;
    out << "============================" <<endl;

    for (int idx = 0; idx < BoardUntils::NUM_TILES; ++idx)
    {
        if (idx % 8 == 0)
            out << endl;

        bool isTileOccupiedIdx = isTileOccupied(idx);

        Piece* piece = nullptr;
        if(isTileOccupiedIdx)
        {
            piece = m_boardBuilder->getBoardConfig().at(idx);
        }

        key = !isTileOccupiedIdx ? '_' :piece->getKeyCharacter();

        if(isTileOccupiedIdx && piece->getAlliance() == Alliance::BLACK)
            key = key + 'a' - 'A';

        out << " " << key;
    }
    out << endl;
}



bool Board::isInCheck(const Alliance alliance) const
{
    bool isChecked = false;

    int kingPosition = -1;
    CollectPiece pieces = getPieces(alliance);
    for (const Piece* piece: pieces)
    {
        if(piece->getPieceType() == PieceType::KING)
        {
            kingPosition = piece->getPosition();
            break;
        }
    }

    Alliance moveMaker = alliance == Alliance::WHITE ? Alliance::BLACK : Alliance::WHITE;

    CollectMove moves = getLegalMoves(moveMaker);
    for (Move* move: moves)
    {
        if(move->getDestCoordinate() == kingPosition)
        {
            isChecked = true;
            break;
        }
    }
    return isChecked;
}

bool Board::hasEscapeMoves(const Alliance alliance) const
{
    CollectPiece pieces = getPieces(alliance);

    CollectMove moves = getLegalMoves(alliance);

    bool hasEscapeMove = false;

    for (Move* move: moves)
    {
        if(move->isLegalMove())
        {
            hasEscapeMove = true;
            break;
        }
    }

    return hasEscapeMove;
}


namespace BOARD{
    Board* createStandardBoard()
    {
        BoardBuilder* boardBuilder = new BoardBuilder();
        boardBuilder->setPiece(new Rook(Alliance::BLACK,   0 ));
        boardBuilder->setPiece(new Knight(Alliance::BLACK, 1 ));
        boardBuilder->setPiece(new Bishop(Alliance::BLACK, 2 ));
        boardBuilder->setPiece(new King(Alliance::BLACK,   3 ));
        boardBuilder->setPiece(new Queen(Alliance::BLACK,  4 ));
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

        boardBuilder->setPiece(new Rook(Alliance::WHITE,   63));
        boardBuilder->setPiece(new Knight(Alliance::WHITE, 62));
        boardBuilder->setPiece(new Bishop(Alliance::WHITE, 61));
        boardBuilder->setPiece(new Queen(Alliance::WHITE,  60));
        boardBuilder->setPiece(new King(Alliance::WHITE,   59));
        boardBuilder->setPiece(new Bishop(Alliance::WHITE, 58));
        boardBuilder->setPiece(new Knight(Alliance::WHITE, 57));
        boardBuilder->setPiece(new Rook(Alliance::WHITE,   56));
        boardBuilder->setPiece(new Pawn(Alliance::WHITE,   55));
        boardBuilder->setPiece(new Pawn(Alliance::WHITE,   54));
        boardBuilder->setPiece(new Pawn(Alliance::WHITE,   53));
        boardBuilder->setPiece(new Pawn(Alliance::WHITE,   52));
        boardBuilder->setPiece(new Pawn(Alliance::WHITE,   51));
        boardBuilder->setPiece(new Pawn(Alliance::WHITE,   50));
        boardBuilder->setPiece(new Pawn(Alliance::WHITE,   49));
        boardBuilder->setPiece(new Pawn(Alliance::WHITE,   48));

        boardBuilder->setMoveMaker(Alliance::WHITE);

        return boardBuilder->build();
    }
}

