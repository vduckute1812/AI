#include "Board.h"
#include "BoardBuilder.h"

Board::Board(const BoardBuilder* builder)
{
    m_boardBuilder = builder;
}
