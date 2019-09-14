#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop: public Piece
{
public:
    Bishop(Alliance pieceAlliance, QWidget *parent = nullptr, unsigned int position = 0);
    virtual ~Bishop();

    virtual bool		isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const;
    virtual bool		isEightColumnExclusion(u32 currentPosition, int candidateOffset) const;

    virtual             MoveCollection calculateLegalMove(const BoardConfig board) const;

};

#endif // BISHOP_H
