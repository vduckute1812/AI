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

private:
    const BoardBuilder*         m_boardBuilder;
};

#endif // BOARD_H

namespace BOARD{
    Board*          createStandardBoard();
}
