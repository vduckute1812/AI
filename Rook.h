#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

const static int ROOK_CANDIDATE_MOVE_COORDINATE[] = { -8, -1, 1, 8 };

class Rook : public Piece
{
public:
    Rook(Alliance pieceAlliance, QWidget *parent = nullptr, int piecePos = -1);
    virtual ~Rook();

    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board) const;

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;

	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

};

#endif
