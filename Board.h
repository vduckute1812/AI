#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>

class Piece;
class BoardBuilder;

typedef std::map<const int, Piece*> BoardConfig;

class Board
{
public:
    Board(const BoardBuilder*);
    const BoardConfig           getBoardConfig();
    const Piece*                getPieceOnBoard(int idx);

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

