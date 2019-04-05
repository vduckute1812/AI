#ifndef MOVE_H
#define MOVE_H

class Board;
class Piece;

enum TypeMove
{
    MAJOR_MOVE,
    ATTACK_MOVE,
    DEFEND_MOVE // NOT YET
};

class Move
{
public:
    Move(const Board* board, const Piece* movePiece, const Piece* attackMove, const int destCoord);
    char*           GetDescription();

    Board*          Do();
    Board*          Undo();

    int             getDestCoordinate();
    bool            isAttackMove();

protected:
    const Board*    m_board;
    const Piece*    m_movePiece;
    const Piece*    m_attackPiece;

    int             m_movedCoordinate;
    int             m_destCoordinate;
    char            m_description[20];
};
#endif // MOVE_H
