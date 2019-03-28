#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include "BoardUntils.h"
#include "Piece.h"
#include "King.h"
#include "Board.h"
#include <QIcon>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    BoardController* controller = nullptr;
	Board window(controller);

    window.setFixedSize(BoardUntils::TILE_ROW_SIZE * BoardUntils::NUM_TILES_PER_ROW,
					BoardUntils::TILE_COL_SIZE * BoardUntils::NUM_TILES_PER_ROW);
    window.setWindowTitle("Chess Game");

    window.setWindowIcon(QIcon("Resources/Kw.svg"));

	window.show();
	return a.exec();
}
