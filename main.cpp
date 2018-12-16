#include "Tile.h"
#include "Board.h"
#include "Piece.h"
#include "Knight.h"

int main(int argc, char *argv[])
{
	BoardController* controller = BoardController::GetInstance();
	Board board(controller);
	board.printBoard();

	system("pause");
	return 0;
}
