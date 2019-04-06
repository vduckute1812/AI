#include "Move.h"
#include "Board.h"
#include "BoardUntils.h"
#include "BoardBuilder.h"

BoardBuilder::BoardBuilder()
{
    for ( int position = 0; position < BoardUntils::NUM_TILES; ++position)
    {
        m_boardConfig.insert(std::pair<int, Piece*> (position, nullptr));
    }
}

Board* BoardBuilder::build()
{
    return new Board(this);
}

BoardBuilder* BoardBuilder::setPiece(Piece* piece)
{
    if (piece != nullptr)
        m_boardConfig.at(piece->getPosition()) = piece;
    return this;
}

BoardBuilder* BoardBuilder::setPiece(int position, Piece* piece)
{
    m_boardConfig.at(position) = piece;
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

