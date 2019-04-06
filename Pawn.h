#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

const static int PAWN_CANDIDATE_MOVE_COORDINATE[] = { 7, 8, 9, 16 };


class Pawn :public Piece
{
public:
    Pawn(Alliance pieceAlliance, int piecePos, QWidget *parent = nullptr);
	~Pawn();

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;
	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

	virtual std::vector<Move*> calculateLegalMove(const Board* board) const;

	int			getDirection() const;
};

#endif
