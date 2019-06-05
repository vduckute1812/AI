#ifndef KING_H
#define KING_H

#include "Piece.h"

const static int KING_CANDIDATE_MOVE_COORDINATE[] = { -9, -8, -7, -1, 1, 7, 8, 9 };

class King :public Piece
{
public:
    King(Alliance pieceAlliance, QWidget *parent = nullptr, int piecePos = -1);
    virtual ~King();

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;
	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

    virtual std::vector<Move*> calculateLegalMove(const BoardState board) const;
};

#endif
