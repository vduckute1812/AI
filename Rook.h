#pragma once
#include "Piece.h"

const static int ROOK_CANDIDATE_MOVE_COORDINATE[] = { -8, -1, 1, 8 };

class Rook : public Piece
{
public:
	Rook(int piecePos, Alliance pieceAlliance);
	~Rook();

	virtual std::vector<Move*> calculateLegalMove(const Board* board) const;

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;

	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

};

