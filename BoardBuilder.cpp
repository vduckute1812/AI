#include "Move.h"
#include "Board.h"
#include "BoardBuilder.h"

BoardBuilder::BoardBuilder()
{

}

Board* BoardBuilder::build()
{
    return new Board(this);
}

BoardBuilder* BoardBuilder::setPiece(BoardConfig config)
{

    for(BoardConfig::iterator it = config.begin(); it != config.end(); ++it) {
        m_boardConfig.insert(std::pair<int, Piece*> (it->first, it->second));
    }    return this;
}

BoardBuilder* BoardBuilder::setMoveMaker(const Alliance nextMoveMaker)
{
    m_nextMoveMaker = nextMoveMaker;
    return this;
}

BoardBuilder* BoardBuilder::setMoveTransition(Move* transitionMove)
{
    m_transitionMove = transitionMove;
    return this;
}
