#pragma once
#include "Singleton.h"
#include "Tile.h"
#include "Piece.h"

class BoardController : public Singleton<BoardController>
{
public:
	void setPiece		( Piece* piece );
	void setMovePiece	( int currentPosition, int destPosition );
	void setMoveMaker	( const Alliance& alliance );
	void setBoard		( std::vector<Tile*> board );

private:
	Alliance			m_nextMoveMaker;
	std::vector<Tile*>	m_board;
};

