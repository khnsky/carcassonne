#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "tile.h"
#include "point.h"
#include "board.h"

#include <stdlib.h>
#include <stdio.h>


int score(sized_board*);

int roadScoreForTwo(board_t, int, int, int, int, direction*);

bool tile_roadCompleted(board_t, int, int, int, int, direction, List*);

bool roadCompleted(board_t, int, int, int, int, direction);

bool tile_castleCompleted(board_t, int, int, int, int, direction, List*);

bool castleCompleted(board_t, size_t, size_t, size_t, size_t, direction);

int tile_numOfNeighbours(board_t, int, int, int, int);

void board_setStatuses(board_t, List*, int);

#endif
