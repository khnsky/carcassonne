#include "ai.h"

#include <limits.h>
#include <math.h>
#include <time.h>

#define ROTATION_MOVES 4

void ai_makeMove(sized_board* board, sized_tlist* list, move* m) {
    if(m == NULL) {
        puts("No more moves available");
        return;
    }

    tile* t = tlist_eraseAt(list, (size_t)move_getTileIndex(m));
    tile_rotate_amount(move_getRotation(m), t);
    board->tiles[move_getRow(m)][move_getColumn(m)] = t;
    move_free(&m);
}

move* ai_bruteForce(sized_board* board, const sized_tlist* list) {
    int best = INT_MIN,
        value;
    rotation_t rotations;
    move* bestMove = move_default();

    // get the List of Points for available moves
    List* moves = getAllPossibleMoves(board);

    for(int i = 0; i < List_getSize(moves); i++) {
        point* p = List_getPoint(moves, i);
        size_t row = point_getRow(p),
               column = point_getColumn(p);
        for(size_t j = 0; j < list->size; j++) {
            // identify to no. of rotations required
            if(tile_isSymmetric(list->tiles[j])) {
                // if all the sides of a tile are the same
                if(tile_isUniform(list->tiles[j])) { rotations = 1; }
                // if opposite sides are identical
                else { rotations = 2; }
            } else { rotations = 4; }
            
            for(int k = 0; k < rotations; k++) {
                // check if tile is applicable at the point
                if(tile_can_place(board, list->tiles[j], row, column)) {
                    // make move
                    board->tiles[row][column] = list->tiles[j];
                    // evaluate
                    value = score(board);
                    // analyze
                    if(value > best) {
                        move_set(bestMove, row, column, j, k, -1);
                        best = value;    
                    }
                    // undo move
                    board->tiles[row][column] = NULL;
                }
                // rotate tile
                tile_rotate(list->tiles[j]);
            }
            // rotate to the initial state
            tile_rotate_amount(ROTATION_MOVES - rotations, list->tiles[j]);
        }
    }
    
    // if failed to get any move 
    if(best == INT_MIN) {
        move_free(&bestMove);
        bestMove = NULL;
    }
    
    List_free(&moves);
    return bestMove;
}

List* getAllPossibleMoves(const sized_board* board) {
   List* list = List_new();

   // if board is empty - place tile in the middle of the board
   if(board_is_empty(board)) {
       List_addFirst(list, point_new(board->size / 2, board->size / 2, 0));
       return list;
   }
   for(size_t i = 0; i < board->size; i++) {
       for(size_t j = 0; j < board->size; j++) {
           if(tile_isEmpty(board->tiles[i][j]) &&
              board_tileHasNeighbour(board, i, j)) {
               List_addLast(list, point_new(i, j, 0));
           }
       }
   }
   return list;
}

List* getMovesForTile(const sized_board* board, const tile* t) {
    List* list = List_new();
    for(size_t i = 0; i < board->size; i++) {
        for(size_t j = 0; j < board->size; j++) {
            if(tile_can_place(board, t, j, i)) {
                List_addLast(list,point_new(i, j, 0));
            }
        }
    }
    return list;
}

int getEmptyCells(const sized_board* board) {
    int num = 0;
    for(size_t i = 0; i < board->size; i++) {
        for(size_t j = 0; j < board->size; j++) {
            if(tile_isEmpty(board->tiles[i][j])) { num++; }
        }
    }
    return num;
}
