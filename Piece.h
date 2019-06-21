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

struct BoardState
{
    static bool         IsTileOccupied(BoardState boarValue, unsigned int position);
    static Piece*       GetPieceOnBoard(BoardState boarValue, unsigned int position);

    void                SetPiece(unsigned int position, Piece* piece);
    MoveCollection      GetMoveCollection(Alliance player);
    unsigned int        GetKingPosition(Alliance player);

    Alliance            m_playerTurn;
    BoardConfig         m_boardValue;
};

class Piece: public QFrame
{
public:
    explicit Piece(Alliance pieceAlliance, PieceType pieceType, PieceValue pieceValue, QWidget *parent = nullptr, unsigned int position = 0);
    virtual ~Piece();

    virtual bool		isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const = 0;
    virtual bool		isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const = 0;

    virtual             MoveCollection calculateLegalMove(const BoardState board) const = 0;

    virtual             PieceValue GetPieceValue() const;

    void                SetPosition(unsigned int position);
    unsigned int        GetPosition() const;

    PieceType			GetPieceType() const;
    Alliance            GetAlliance() const;

    char                GetKeyCharacter() const;

    QLabel*             GetRenderImg() const;

    void                SetFirstMove(bool firstMove);
    bool                IsFirstMove() const;

protected:
    unsigned int        m_piecePosition;
    Alliance			m_pieceAlliance;
    PieceType           m_pieceType;
    PieceValue          m_pieceValue;
    QLabel*             m_pieceImg;

    bool                m_isFirstMove;
};

#endif // PIECE_H
