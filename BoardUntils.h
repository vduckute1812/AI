#ifndef BOARDUNTILS_H
#define BOARDUNTILS_H
#include "Defines.h"


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

    static bool IsNumColumn(int numColumn ,int coordinate)
    {
        if(coordinate < 0 && coordinate >= getMaxTiles())
        {
            throw "Not in range of board!";
        }

        int firstColum = numColumn;
        while(firstColum < getMaxTiles())
        {
            if(firstColum == coordinate)
                return true;

            firstColum += NUM_TILES_PER_COL;
        }
        return false;
    }
};

#endif // BOARDUNTILS_H
