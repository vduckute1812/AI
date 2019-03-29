#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>

class Tile;
class Piece;
class BoardBuilder;

typedef std::map<int, Tile*> BoardTiles;
typedef std::map<const int, Piece*> BoardConfig;

class Board
{
public:
    Board(const BoardBuilder*);
    void            setBoardConfig(BoardConfig);

private:
    BoardTiles                  m_tiles;
    const BoardBuilder*         m_boardBuilder;
    BoardConfig                 m_boardConfig;
};

#endif // BOARD_H

Board* createStandardBoard();
