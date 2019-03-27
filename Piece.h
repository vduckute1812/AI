#ifndef PIECE_H
#define PIECE_H

#include <QFrame>
#include <QLabel>

enum Alliance
{
    WHITE = 'w',
    BLACK = 'b'
};

enum PieceType
{
    ROOK	= 'R',
    KNIGHT	= 'K',
    BISHOP	= 'B',
    QUEEN	= 'Q',
    KING	= 'Z',
    PAWN	= 'P'
};

class Move;
class Board;
class Piece: public QFrame
{
public:
    explicit Piece(int position, Alliance pieceAlliance, PieceType pieceType, QWidget *parent = nullptr);
    virtual ~Piece();

    virtual bool		isFirstColumnExclusion(int currentPosition, int candidateOffset) const = 0;
    virtual bool		isEightColumnExclusion(int currentPosition, int candidateOffset) const = 0;

    virtual             std::vector<Move*> calculateLegalMove(const Board* board) const = 0;

    void                setPosition(int position);
    int                 getPosition() const;

    PieceType			getPieceType() const;
    Alliance            getAlliance() const;

protected:
    int                 m_piecePosition;
    Alliance			m_pieceAlliance;
    PieceType           m_pieceType;
    QLabel*             m_pieceImg;
};

#endif // PIECE_H
