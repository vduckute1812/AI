#ifndef BOARDUNTILS_H
#define BOARDUNTILS_H
#include "Defines.h"
#include "Piece.h"


enum CheckColumn
{
    FIRST   = 0,
    SECOND  = 1,
    NEAR_END_OF_COL = NUM_TILES_PER_COL - 2,
    END_OF_COL      = NUM_TILES_PER_COL - 1
};

struct BoardUntils
{

    static int getMaxTiles() {return NUM_TILES_PER_ROW * NUM_TILES_PER_COL;}

    static bool IsNumColumn(unsigned int numColumn ,int coordinate)
    {
        if(coordinate < 0 && coordinate >= getMaxTiles())
        {
            throw "Not in range of board!";
        }

        unsigned int firstColum = numColumn - 1;
        while(firstColum < getMaxTiles())
        {
            if(firstColum == coordinate)
                return true;

            firstColum += NUM_TILES_PER_COL;
        }
        return false;
    }

    static bool IsValidTileCandidate(int coordinate)
    {
        if(coordinate < 0 || coordinate >= getMaxTiles())
        {
            return false;
        }
        return true;
    }

    static bool IsSameAlliance(Alliance piece1, Alliance piece2)
    {
        if ((piece1 == Alliance::BLACK && piece2 == Alliance::BLACK)
            || (piece1 == Alliance::WHITE && piece2 == Alliance::WHITE))
        {
            return true;
        }
return false;
    }
};

#endif // BOARDUNTILS_H
