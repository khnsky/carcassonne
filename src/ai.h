#ifndef AI_H
#define AI_H

#include "board.h"
#include "calculator.h"
#include "move.h"
#include "point.h"
#include "tile.h"
#include "tlist.h"

/**
* Finds the best move by Brute Force Search Algorithm 
* @param [in] game board
* @param [in] list with available tiles
* @return best move
*/
move* ai_bruteForce(sized_board*, const sized_tlist*);

/**
* Makes the move: takes a tile from the lsit and places it on the board
* @param [in] game board
* @param [in] list with available tiles
* @param [in] the move to be done
*/
void ai_makeMove(sized_board*, sized_tlist*, move*);

/**
* Determines all board's cells available for moves 
* @param [in] game board
* @return list of cells available for moves
*/
List* getAllPossibleMoves(const sized_board*);

/**
* Determines all board's cells available for the tile to be placed
* @param [in] game board
* @param [in] tile to be placed
* @return list of cells available for moves
*/
List* getMovesForTile(const sized_board*, const tile*);

/**
* Determines the number of free cells
* @param [in] game sized_board
* @return number of free cells
*/
int getEmptyCells(const sized_board*);

#endif
