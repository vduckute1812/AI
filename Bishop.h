#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

const static int BISHOP_CANDIDATE_MOVE_COORDINATE[] = { -9, -7, 7, 9 };

class Bishop: public Piece
{
public:
    Bishop(int position, Alliance pieceAlliance , QWidget *parent = nullptr);
    virtual ~Bishop();

    virtual bool		isFirstColumnExclusion(int currentPosition, int candidateOffset) const;
    virtual bool		isEightColumnExclusion(int currentPosition, int candidateOffset) const;

    virtual             std::vector<Move*> calculateLegalMove(const Board* board) const;

};

#endif // BISHOP_H
