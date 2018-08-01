#ifndef MOVE_H
#define MOVE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct move move;

move* move_default();
move* move_new(int, int, int, int);
move* move_newFromScore(int);
void move_free(move**);
int move_getRow(const move*);
int move_getColumn(const move*);
int move_getTileIndex(const move*);
int move_getRotation(const move*);
int move_getScore(const move*);
void move_set(move*, int, int, int, int, int);
void move_setPoint(move*, int, int);
void move_setTile(move*, int, int);
void move_setScore(move*, int);
bool move_isEmpty(const move*);
bool move_isEqual(const move*, const move*);
void move_print(const move*);

#endif
