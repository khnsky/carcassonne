#include "move.h"

#include <stdio.h>

struct move {
    int row;
    int column;
    int tileIndex;
    int rotation;
    int score;
};

move* move_new(int row, int col, int index, int rotation) {
    move* self = malloc(sizeof(move)); 
    self->row = row;
    self->column = col;
    self->tileIndex = index;
    self->rotation = rotation;
    return self;
}

move* move_default() {
    move* self = malloc(sizeof(move)); 
    self->row = self->column = self->tileIndex = self->rotation = -1;
    return self;
}

move* move_newFromScore(int score) {
    move* self =move_default();
    self->score = score;
    return self;
}

void move_free(move** selfPtr) {
    free(*selfPtr);
    *selfPtr = NULL;
}

int move_getRow(const move* self) { return self->row; }

int move_getColumn(const move* self) { return self->column; }

int move_getTileIndex(const move* self) { return self->tileIndex; }

int move_getRotation(const move* self) { return self->rotation; }

int move_getScore(const move* self) { return self->score; }

void move_set(move* self, int row, int col, int index, int rotation, int score) {
    self->row = row;
    self->column = col;
    self->tileIndex = index;
    self->rotation = rotation;
    self->score = score;
}

void move_setPoint(move* self, int row, int col) {
    self->row = row;
    self->column = col;
}
void move_setTile(move* self, int index, int rotation) {
    self->tileIndex = index;
    self->rotation = rotation;
}

void move_setScore(move* self, int score) { self->score = score; }

bool move_isEmpty(const move* self) { return self->tileIndex == -1; }

bool move_isEqual(const move* self, const move* m) {
    return self->row       == m->row
        && self->column    == m->column
        && self->tileIndex == m->tileIndex
        && self->rotation  == m->rotation;
}

void move_print(const move* self) {
    printf("Tile with index %i, "
           "rotated by %i dergees is placed at point (%i, %i), "
           "produces final score of %i\n",
           self->tileIndex, self->rotation * 90, self->row, self->column, self->score);
}
