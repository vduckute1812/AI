#ifndef KING_H
#define KING_H

#include "Piece.h"

class King :public Piece
{
public:
    King(Alliance pieceAlliance, QWidget *parent = nullptr, unsigned int piecePos = 0);
    virtual ~King();

    virtual bool isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const;
    virtual bool isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

    virtual std::vector<Move*> calculateLegalMove(const BoardState board) const;
};

#endif
