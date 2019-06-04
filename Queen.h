#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

const static int QUEEN_CANDIDATE_MOVE_COORDINATE[] = { -9, -8, -7, -1, 1, 7, 8, 9 };

class Queen:public Piece
{
public:
    Queen(Alliance pieceAlliance, QWidget *parent = nullptr, int piecePos = -1);
    virtual ~Queen();

    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board) const;

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;

	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

};

#endif
