#ifndef MOVE_H
#define MOVE_H

#include "tile.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct move move;

move* move_alloc(void);
move* move_new(size_t, size_t, size_t, rotation_t);
void move_free(move**);
size_t move_getRow(const move*);
size_t move_getColumn(const move*);
size_t move_getTileIndex(const move*);
rotation_t move_getRotation(const move*);
int move_getScore(const move*);
void move_set(move*, size_t, size_t, size_t, rotation_t, int);
void move_setPoint(move*, size_t, size_t);
void move_setTile(move*, size_t, rotation_t);
void move_setScore(move*, int);

#endif
