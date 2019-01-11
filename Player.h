#pragma once
#include <vector>
#include "Piece.h"

class Move;
class Board;
class Player
{
public:
    Player(const Board* board, Alliance alliance);
    virtual ~Player();

	bool					isInCheck();
	bool					isInCheckMate();
    bool                    checkLegalMove(Move* move);
	std::vector<Move*>		calculateActacksOnTile(int piecePosition, std::vector<Move*> moves);

protected:

    virtual std::vector<Move*>  calculateKingCastles(const std::vector<Move*> playerLegals,
                                                const std::vector<Move*> opponentLegals) = 0;


    bool                    hasEscapeMoves();



	const Piece*			m_King;
	std::vector<Piece*>		m_pieces;
	Alliance				m_alliance;
	bool					m_isInCheck;
};

