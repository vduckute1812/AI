#ifndef BOARD_H
#define BOARD_H
#include "Defines.h"
#include "Messenger.h"

class Piece;
typedef std::pair<const int, SharedPtr<Piece>> PieceInf;

typedef std::vector<PieceInf> BoardConfig;
typedef std::vector<const SharedPtr<Piece>> CollectPiece;

class Board: public Messenger
{
public:
    Board(BoardConfig);

    BoardConfig        GetBoardConfig() const;

private:
    BoardConfig         m_boardConfig;
};

#endif // BOARD_H
