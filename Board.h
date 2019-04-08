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

    CollectPiece                getCurrentPieces() const;
    CollectPiece                getOpponentPieces() const;

    CollectMove                 getLegalMoves() const;
    CollectMove                 getOpponentMoves() const;

    const Piece*                getPieceOnBoard(int idx) const;

    void                        printBoard() const;

    bool                        isTileOccupied(const int idx) const;
    bool                        isCheckedByEnemy() const;

private:

    const BoardBuilder*         m_boardBuilder;    
};

namespace BOARD
{
    Board*          createStandardBoard();
}

#endif // BOARD_H

