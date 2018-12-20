#pragma once

#include "Piece.h"

const static int KING_CANDIDATE_MOVE_COORDINATE[] = { -9, -8, -7, -1, 1, 7, 8, 9 };

class King :public Piece
{
public:
	King(int piecePos, Alliance pieceAlliance);
	~King();

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;
	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

	virtual std::vector<Move*> calculateLegalMove(const Board* board) const;
};

