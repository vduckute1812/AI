#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>
#include "Piece.h"

class BoardBuilder;

typedef std::map<const int, Piece*> BoardConfig;

class Board
{
public:
    Board(const BoardBuilder*);

    const BoardConfig           getBoardConfig() const;
    Alliance                    getMoveMaker() const;
    Alliance                    getOpponentMaker() const;

    const Piece*                getPieceOnBoard(int idx) const;

    void                        printBoard() const;

    bool                        isTileOccupied(const int idx) const;

private:

    const BoardBuilder*         m_boardBuilder;    
};

namespace BOARD
{
    Board*          createStandardBoard();
}

#endif // BOARD_H

