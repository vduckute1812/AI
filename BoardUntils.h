#ifndef BOARDUNTILS_H
#define BOARDUNTILS_H

#include "Piece.h"

static const int FIRST_COLUMN[]   = { 0,  8, 16, 24, 32, 40, 48, 56 };
static const int SECOND_COLUMN[]  = { 1,  9, 17, 25, 33, 41, 49, 57 };
static const int SEVENTH_COLUMN[] = { 6, 14, 22, 30, 38, 46, 54, 62 };
static const int EIGHTH_COLUMN[]  = { 7, 15, 23, 31, 39, 47, 55, 63 };

struct BoardUntils
{
public:
	const static int NUM_TILES = 64;

	const static int TILE_ROW_SIZE = 50;
	
	const static int TILE_COL_SIZE = 50;

	const static int NUM_TILES_PER_ROW = 8;

	static bool isFirstColumn(int coordinate)
	{
		for (int candidateCoordinate: FIRST_COLUMN)
		{
			if (coordinate == candidateCoordinate)
				return true;
		}

		return false;
	}

	static bool isSecondColumn(int coordinate)
	{
		for (int candidateCoordinate: SECOND_COLUMN)
		{
			if (coordinate == candidateCoordinate)
			{
				return true;
			}
		}

		return false;
	}

	static bool isSeventhColumn(int coordinate)
	{
		for (int candidateCoordinate : SEVENTH_COLUMN)
		{
			if (coordinate == candidateCoordinate)
				return true;
		}

		return false;
	}

	static bool isEighthColumn(int coordinate)
	{
		for (int candidateCoordinate : EIGHTH_COLUMN)
		{
			if (coordinate == candidateCoordinate)
				return true;
		}

		return false;
	}


	static bool isValidTileCandidate(int coordinate)
	{
		return coordinate >= 0 && coordinate < NUM_TILES;
	}

    static bool isSameAlliance(Alliance piece1, Alliance piece2)
    {
        if ((piece1 == Alliance::BLACK && piece2 == Alliance::BLACK)
            || (piece1 == Alliance::WHITE && piece2 == Alliance::WHITE))
        {
            return true;
        }
        return false;
    }
};

#endif
