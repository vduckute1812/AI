#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn :public Piece
{
public:
    Pawn(Alliance pieceAlliance, QWidget *parent = nullptr, unsigned int piecePos = 0);
	~Pawn();

    virtual bool isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const;
    virtual bool isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

    virtual std::vector<Move*> calculateLegalMove(const BoardState board) const;

	int			getDirection() const;
};

#endif
