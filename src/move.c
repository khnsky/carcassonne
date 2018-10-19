#include "move.h"

#include <stdio.h>

struct move {
    size_t row;
    size_t column;
    size_t tileIndex;
    rotation_t rotation;
    int score;
};

move* move_new(size_t row, size_t col, size_t index, rotation_t rotation) {
    move* self = malloc(sizeof(move));
    // TODO: score not set?
    *self = (move) {
        .row       = row,
        .column    = col,
        .tileIndex = index,
        .rotation  = rotation
    };
    return self;
}

move* move_alloc() { return malloc(sizeof(move)); }

void move_free(move** selfPtr) {
    free(*selfPtr);
    *selfPtr = NULL;
}

size_t move_getRow(const move* self) { return self->row; }

size_t move_getColumn(const move* self) { return self->column; }

size_t move_getTileIndex(const move* self) { return self->tileIndex; }

rotation_t move_getRotation(const move* self) { return self->rotation; }

int move_getScore(const move* self) { return self->score; }

void move_set(move* self, size_t row, size_t col,
              size_t index, rotation_t rotation, int score) {
    *self = (move) { row, col, index, rotation, score };
}

void move_setPoint(move* self, size_t row, size_t col) {
    self->row    = row;
    self->column = col;
}

void move_setTile(move* self, size_t index, rotation_t rotation) {
    self->tileIndex = index;
    self->rotation  = rotation;
}

void move_setScore(move* self, int score) { self->score = score; }
