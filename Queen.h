#pragma once
#include "Piece.h"

const static int QUEEN_CANDIDATE_MOVE_COORDINATE[] = { -9, -8, -7, -1, 1, 7, 8, 9 };

class Queen:public Piece
{
public:
	Queen(int piecePos, Alliance pieceAlliance, QWidget *parent = nullptr);
	~Queen();

	virtual std::vector<Move*> calculateLegalMove(const Board* board) const;

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;

	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

};

