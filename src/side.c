#include "side.h"

#include <stdlib.h>

side* side_new(element type) {
    side* self = malloc(sizeof(side));
    *self = (side) { .type = type, .completion = 0 };
    return self;
}

side* side_newDefault() {
    side* self = malloc(sizeof(side));
    *self = (side) { .type = -1, .completion = 0 };
    return self;
}

side* side_copy(const side* self) {
    side* copy = malloc(sizeof(side));
    *copy = (side) { .type = self->type, .completion = self->completion };
    return copy;
}

void side_free(side** selfPtr) {
    free(*selfPtr);
    *selfPtr = NULL;
}

element side_getType(const side* self) { return self->type; }

void side_setType(side* self, element type) { self->type = type; }

int side_isCompleted(const side* self) { return self->completion; }

void side_setCompletionStatus(side* self, int compl) { self->completion = compl; }

direction direction_getOpposite(direction dir) {
    switch (dir) {
    case NORTH: return SOUTH;
    case EAST: return WEST;
    case SOUTH: return NORTH;
    case WEST: return EAST;
    }
    assert(dir >= NORTH && dir <= WEST && "invalid direction");
    UNREACHABLE();
}

bool direction_areOpposite(direction dir1, direction dir2) {
    return dir1 == direction_getOpposite(dir2);
}
