#pragma once
#include "Piece.h"

const static int BISHOP_CANDIDATE_MOVE_COORDINATE[] = { -9, -7, 7, 9 };

class Bishop : public Piece
{
public:
	Bishop(int piecePos, Alliance pieceAlliance);
	~Bishop();

	virtual const std::vector<Move*> calculateLegalMove(const Board* board) const;

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;
	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

};

