#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen:public Piece
{
public:
    Queen(Alliance pieceAlliance, QWidget *parent = nullptr, unsigned int piecePos = 0);
    virtual ~Queen();

    virtual std::vector<Move*> calculateLegalMove(const BoardState board) const;

    virtual bool isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

    virtual bool isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

};

#endif
