#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include "Piece.h"
#include "Singleton.h"
#include "BoardUI.h"

class Move;
class BoardController: public Singleton<BoardController>
{
public:
    void        InitGame();
    void        setBoard(Board*);

    void        printCurrentBoard();
    void        freeGame();

    void        setSelectedPiece(Piece* piece);
    Piece*      getSelecetedPiece() const;

    Alliance    getMoveMaker();
private:
    Piece*          m_selectedPiece;
    BoardUI*        m_boardGame;
    Alliance        m_moveMaker;
};

#endif // BOARDCONTROLLER_H
