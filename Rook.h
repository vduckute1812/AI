#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(Alliance pieceAlliance, QWidget *parent = nullptr, unsigned int piecePos = 0);
    virtual ~Rook();

    virtual std::vector<Move*> calculateLegalMove(const BoardState board) const;

    virtual bool isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

    virtual bool isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

};

#endif
