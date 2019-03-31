#ifndef MOVE_H
#define MOVE_H

class Board;
class Piece;

enum TYPE_MOVE
{
    MAJOR_MOVE,
    ATTACK_MOVE,
    DEFEND_MOVE // NOT YET
};

class Move
{
public:
    Move(const Board* board, const Piece* movePiece, const int destCoord);
    char*           GetDescription();

    void            Do();
    void            Undo();

protected:
    const Board*    m_board;
    const Piece*    m_movePiece;
    int             m_destCoordinate;
    char            m_description[20];
};
#endif // MOVE_H
