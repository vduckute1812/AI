#include "chessgame.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include "BoardUntils.h"
#include "Piece.h"
#include "King.h"
#include "Board.h"

class BoardRender : public QWidget {

public:
	BoardRender(QWidget *parent = nullptr);
};

BoardRender::BoardRender(QWidget *parent): QWidget(parent) 
{
	King *king = new King(0, Alliance::BLACK, this);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	BoardController* controller;
	Board window(controller);

	window.resize(BoardUntils::TILE_ROW_SIZE * BoardUntils::NUM_TILES_PER_ROW, 
					BoardUntils::TILE_COL_SIZE * BoardUntils::NUM_TILES_PER_ROW);
	window.setWindowTitle("Board");
	window.show();
	return a.exec();
}
