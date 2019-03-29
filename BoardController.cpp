#include "BoardUntils.h"
#include "BoardController.h"

BoardController::BoardController()
{

}


BoardTiles BoardController::createTableTiles()
{
    BoardTiles tableTiles;
    Piece* NULL_PIECE = nullptr;

    for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
    {
        tableTiles.insert(std::pair<int, Tile*>(i,  new Tile(i, NULL_PIECE)));
    }

    return tableTiles;
}

void BoardController::InitGame()
{

}
