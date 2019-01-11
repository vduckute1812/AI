#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include "BoardUntils.h"
#include "Piece.h"
#include "King.h"
#include "Board.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    BoardController* controller = nullptr;
	Board window(controller);

    window.setFixedSize(BoardUntils::TILE_ROW_SIZE * BoardUntils::NUM_TILES_PER_ROW,
					BoardUntils::TILE_COL_SIZE * BoardUntils::NUM_TILES_PER_ROW);
	window.setWindowTitle("Board");
	window.show();
	return a.exec();
}
