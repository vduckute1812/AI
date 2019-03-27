#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>

class Tile;
class BoardBuilder;
class Board
{
public:
    Board(const BoardBuilder*);

private:
    const BoardBuilder*         m_boardBuilder;
    std::vector<Tile*>          m_tiles;
};

#endif // BOARD_H
