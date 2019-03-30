#ifndef KNIGHT_H
#define KNIGHT_H


#include "Piece.h"

const static int KNIGHT_CANDIDATE_MOVE_COORDINATE[] = { -17, -15, -10, -6, 6, 10, 15, 17 };

class Knight : public Piece
{
public:

    Knight(Alliance pieceAlliance, int piecePosition, QWidget *parent = nullptr);
    virtual ~Knight();
	
	virtual std::vector<Move*> calculateLegalMove(const Board* board)  const;

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;
	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

	bool isSecondColumnExclusion(int currentPosition, int candidateOffset) const;
	bool isSeventhColumnExclusion(int currentPosition, int candidateOffset) const;

};

#endif
