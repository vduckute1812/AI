#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop: public Piece
{
public:
    Bishop(Alliance pieceAlliance, QWidget *parent = nullptr, unsigned int position = 0);
    virtual ~Bishop();

    virtual bool		isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const;
    virtual bool		isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const;

    virtual             MoveCollection calculateLegalMove(const BoardState board) const;

};

#endif // BISHOP_H
