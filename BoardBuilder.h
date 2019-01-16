#ifndef BOARDBUILDER_H
#define BOARDBUILDER_H
#include <map>
#include "Piece.h"

class Move;
class BoardBuilder
{
public:
    BoardBuilder();

private:
    std::map<int, Piece*>   m_boardConfig;
    Alliance                m_nextMoveMaker;
    Move*                   m_transitionMove;
};

#endif // BOARDBUILDER_H
