#ifndef BOARDBUILDER_H
#define BOARDBUILDER_H

#include "Piece.h"
#include <map>

class Move;
class Board;
typedef std::map<const int, Piece*> BoardConfig;

class BoardBuilder
{
public:
    explicit                BoardBuilder();

    Board*                  build();
    BoardBuilder*           setPiece(Piece* piece);
    BoardBuilder*           setMoveMaker(const Alliance nextMoveMaker);
    BoardBuilder*           setMoveTransition(Move* transitionMove);

    BoardConfig             getBoardConfig() const;

private:
    Board*          m_fromBoard;
    Move*           m_transitionMove;
    Alliance        m_nextMoveMaker;
    BoardConfig     m_boardConfig;
};

#endif // BOARDBUILDER_H
