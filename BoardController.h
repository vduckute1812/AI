#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "Singleton.h"
#include "Piece.h"

class BoardController: public Singleton<BoardController>
{
public:
    void				setPiece		( Piece* piece );
    void				movePiece		( Move* move );
    void				setMoveMaker	( const Alliance& alliance );
    void				setBoard		( Board* m_board );

    Board*				getBoard();
    Alliance            getMoveMaker();

    void				setSelectedPiece(Piece* piece);
    Piece*				getSelectedPiece();

private:
    Alliance			m_nextMoveMaker;
    Board*				m_board;
    Piece*				m_currentPiece;
};

#endif // BOARDCONTROLLER_H
