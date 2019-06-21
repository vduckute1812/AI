#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>
#include "Piece.h"

class BoardBuilder;

typedef std::map<const int, Piece*> BoardConfig;
typedef std::vector<const Piece*> CollectPiece;

typedef std::vector<Move*> CollectMove;

class Board
{
public:
    Board(const BoardBuilder*);
    ~Board();

    const BoardConfig           getBoardConfig() const;
    Alliance                    getMoveMaker() const;
    Alliance                    getOpponentMaker() const;

    CollectPiece                getPieces(const Alliance alliance) const;

    CollectMove                 getLegalMoves(const Alliance alliance) const;

    const Piece*                getPieceOnBoard(int idx) const;

    void                        printBoard() const;

    bool                        isTileOccupied(const int idx) const;

    bool                        isInCheck(const Alliance alliance) const;
    bool                        hasEscapeMoves(const Alliance alliance) const;

    void                        setAIblack(bool black);
    void                        setAIwhite(bool white);

    bool                        isAIPlayer();

private:

    const BoardBuilder*         m_boardBuilder;
    bool                        m_isAIblack;
    bool                        m_isAIwhite;
};

namespace BOARD
{
    Board*          createStandardBoard();
}

#endif // BOARD_H

