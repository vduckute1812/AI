#ifndef KNIGHT_H
#define KNIGHT_H


#include "Piece.h"

class Knight : public Piece
{
public:

    Knight(Alliance pieceAlliance, QWidget *parent = nullptr, unsigned int piecePosition = 0);
    virtual ~Knight();
	
    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board)  const;

    virtual bool isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const;
    virtual bool isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

    bool isSecondColumnExclusion(unsigned int currentPosition, int candidateOffset) const;
    bool isSeventhColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

};

#endif
