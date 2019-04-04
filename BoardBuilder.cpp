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

BoardBuilder* BoardBuilder::setPiece(Piece* piece)
{
    m_boardConfig.insert(std::pair<int, Piece*> (piece->getPosition(), piece));
    return this;
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

Alliance BoardBuilder::getMoveMaker() const
{
    return m_nextMoveMaker;
}

BoardConfig BoardBuilder::getBoardConfig() const
{
    return m_boardConfig;
}

