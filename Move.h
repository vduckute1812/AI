#ifndef MOVE_H
#define MOVE_H

class Board;
class Piece;

enum TypeMove
{
    MAJOR_MOVE,
    ATTACK_MOVE,
    DEFEND_MOVE, // NOT YET
    PAWN_PROMOTION,  // NOT YET
    KING_SIDE_CASTLE, // NOT YET
    QUEEN_SIDE_CASTLE, // NOT YET
    CHECK_MOVE  // NOT YET
};

class Move
{
public:
    Move(const Board* board, const Piece* movePiece, const Piece* attackMove, const int destCoord);
    char*           GetDescription();

    Board*          Execute();
    Board*          UndoExecute();

    // Use on Board
    Board*          Redo();
    Board*          Undo();

    const Board*    getTransitionBoard() const;

    int             getMoveCoordinate() const;
    int             getDestCoordinate() const;
    bool            isAttackMove() const;

    bool            isLegalMove();

protected:
    const Board*    m_board;
    const Board*    m_toBoard;
    const Piece*    m_movePiece;
    const Piece*    m_attackPiece;

    bool            m_isFirstMove;
    int             m_movedCoordinate;
    int             m_destCoordinate;
    char            m_description[20];
};
#endif // MOVE_H
