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

enum PieceValue
{
    PAWN_VALUE =    100,
    KNIGHT_VALUE =  300,
    BISHOP_VALUE =  300,
    ROOK_VALUE =    500,
    QUEEN_VALUE =   900,
    KING_VALUE =    1000
};

class Move;
class Board;
class Move;
class Piece;

typedef std::vector<Move*> MoveCollection;

typedef std::pair<unsigned int, Piece*> PieceInf;

typedef std::vector<PieceInf> BoardConfig;
typedef std::vector<const Piece*> CollectPiece;

class Piece: public QFrame
{
public:
    explicit Piece(Alliance pieceAlliance, PieceType pieceType, PieceValue pieceValue, QWidget *parent = nullptr, int position = -1);
    virtual ~Piece();

    virtual bool		isFirstColumnExclusion(int currentPosition, int candidateOffset) const = 0;
    virtual bool		isEightColumnExclusion(int currentPosition, int candidateOffset) const = 0;

    virtual             MoveCollection calculateLegalMove(const BoardConfig board) const = 0;

    virtual             PieceValue GetPieceValue() const;

    void                SetPosition(int position);
    int                 GetPosition() const;

    PieceType			GetPieceType() const;
    Alliance            GetAlliance() const;

    char                GetKeyCharacter() const;

    QLabel*             GetRenderImg() const;

    void                SetFirstMove(bool firstMove);
    bool                IsFirstMove() const;

protected:
    int                 m_piecePosition;
    Alliance			m_pieceAlliance;
    PieceType           m_pieceType;
    PieceValue          m_pieceValue;
    QLabel*             m_pieceImg;

    bool                m_isFirstMove;
};

#endif // PIECE_H
