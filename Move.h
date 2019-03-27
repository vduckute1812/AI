#ifndef MOVE_H
#define MOVE_H

class Board;
class Piece;

class Move
{
public:
    Move(const Board* board, const Piece* movePiece, const int destCoord);
protected:
    const Board*    m_board;
    const Piece*    m_movePiece;
    int             m_destCoordinate;
};

class MajorMove: public Move
{
public:
    MajorMove(const Board* board, const Piece* movePiece, const int destCoord);
};

class AttackMove: public Move
{
public:
    AttackMove(const Board* board, const Piece* movePiece, const int destCoord, const Piece* attackedPiece);
private:
    const Piece*        m_attackedPiece;
};

#endif // MOVE_H
