#include "tile.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

tile* tile_alloc(void) { return calloc(1, sizeof(tile)); }

tile* tile_alloc_asgn(tile** ptr) { return *ptr = tile_alloc(); }

element elem_from_char(char ch) {
    assert(ch == 'c' || ch == 'r' || ch == 'f');
    switch (tolower(ch)) {
    case 'c': return CASTLE;
    case 'r': return ROAD;
    default:  return FIELD;
    }
}

modifier mod_from_char(char ch) {
    switch (tolower(ch)) {
    case '*': return SHIELD;
    case 't': return TEMPLE;
    default:  return NONE;
    }
}

tile* tile_from_str(const char str[static 5], tile* t) {
    if (t) {
        *t = (tile) {
            .up    = side_new(elem_from_char(str[0])),
            .right = side_new(elem_from_char(str[1])),
            .down  = side_new(elem_from_char(str[2])),
            .left  = side_new(elem_from_char(str[3])),
            .mod   = mod_from_char(str[4]),
        };

        if(tile_numOfSegments(t, ROAD) > 2) { t->mod = CROSSROASDS; }
    }
    return t;
}

tile* tile_alloc_from_str(const char str[static 5]) {
    tile* t;
    return tile_alloc_from_str_asgn(str, &t);
}

tile* tile_alloc_from_str_asgn(const char str[static 5], tile** ptr) {
    return tile_from_str(str, tile_alloc_asgn(ptr));
}

tile* tile_alloc_from_tile(const tile* orig) {
    if (orig) {
        tile* new = tile_alloc();
        *new = (tile) {
            .up    = side_copy(orig->up),
            .right = side_copy(orig->right),
            .down  = side_copy(orig->down),
            .left  = side_copy(orig->left),
            .mod   = orig->mod,
        };
        return new;
    }
    return NULL;
}

void tile_free(tile* t) {
    if (t) {
        side_free(&t->up);
        side_free(&t->right);
        side_free(&t->down);
        side_free(&t->left);
    }
}


bool tile_parse(FILE* file, tile** t) {
    int ch;
    char str[5];
    size_t i = 0;
    while ((ch = getc(file)) != EOF) {
        if (ch == '\t') { return true; }
        if (isspace(ch)) { continue; }
        str[i++] = (char)ch;
        if (i == 5) {
            tile_alloc_from_str_asgn(str, t);
            return true;
        }
    }
    return false;
}

char elem_to_char(element e) {
    switch (e) {
    case CASTLE: return 'c';
    case ROAD:   return 'r';
    case FIELD:  return 'f';
    default:     return '\0';
    }
}

char mod_to_char(modifier m) {
    switch (m) {
    case SHIELD: return '*';
    case TEMPLE: return 't';
    default:     return '_';
    }
}

char* tile_to_str(const tile* t, char buff[static 5]) {
    if (t && buff) {    // check if pointers are not null
        buff = (char[5]) {
            elem_to_char(tile_getSideElement(t, NORTH)),
            elem_to_char(tile_getSideElement(t, EAST)),
            elem_to_char(tile_getSideElement(t, SOUTH)),
            elem_to_char(tile_getSideElement(t, WEST)),
            mod_to_char(t->mod),
        };
    }
    else if (buff) {    // null tile pointer should mean empty board cell
        buff = (char[5]) { '\t', '\0', '\0', '\0', '\0' };
    }
    return buff;
}

char* tile_to_str_alloc(const tile* t) {
    return tile_to_str(t, malloc(sizeof(char) * 5));
}

void tile_print(const tile* t) {
    char buff[5];
    printf("%.*s", 5, tile_to_str(t, buff));
}

tile* tile_rotate(tile* t) {
    if (t) {
        tile temp = {
            .up    = t->left,
            .right = t->up,
            .down  = t->right,
            .left  = t->down,
            .mod   = t->mod,
        };
        *t = temp;
    }
    return t;
}

void rotation_print(rotation_t rot) {
    switch (rot) {
    case ROT_90:
        fputs("90 degrees", stdout);
        return;
    case ROT_180:
        fputs("180 degrees", stdout);
        return;
    case ROT_270:
        fputs("270 degrees", stdout);
        return;
    default: { ; }
    }
}

tile* tile_rotate_amount(rotation_t rot, tile* t) {
    assert(rot >= ROT_NO && rot <= ROT_270 && "invalid rotation");
    while(rot--) { tile_rotate(t); }
    return t;
}

bool tile_isEmpty(const tile* t) { return t == 0; }

element tile_getSideElement(const tile* t, direction dir) {
    switch (dir) {
    case NORTH: return side_getType(t->up);
    case EAST:  return side_getType(t->right);
    case SOUTH: return side_getType(t->down);
    case WEST:  return side_getType(t->left);
    }
    assert(dir <= NORTH && dir >= WEST && "invalid rotation");
}

side* tile_getSide(const tile* t, direction dir) {
    switch (dir) {
    case NORTH: return t->up;
    case EAST:  return t->right;
    case SOUTH: return t->down;
    case WEST:  return t->left;
    }
    return 0;
}

void tile_setSideCompletion(const tile* t, direction dir, int status) {
    side_setCompletionStatus(tile_getSide(t, dir), status);
}

int tile_getSideCompletion(const tile* t, direction dir) {
    switch (dir) {
    case NORTH: return side_isCompleted(t->up);
    case EAST:  return side_isCompleted(t->right);
    case SOUTH: return side_isCompleted(t->down);
    case WEST:  return side_isCompleted(t->left);
    }
    return 0;
}

modifier tile_getCenter(const tile* t) { return t->mod; }

size_t tile_numOfSegments(const tile* t, element type) {
    size_t count = 0;
    if (side_getType(t->up)    == type) { count++; }
    if (side_getType(t->right) == type) { count++; }
    if (side_getType(t->down)  == type) { count++; }
    if (side_getType(t->left)  == type) { count++; }
    return count;
}

direction* tile_getSegments(const tile* t, element type, size_t count) {
    direction* segments = malloc(count * sizeof(direction));
    size_t i = 0;
    if (side_getType(t->up)    == type) { segments[i++] = NORTH; }
    if (side_getType(t->right) == type) { segments[i++] = EAST; }
    if (side_getType(t->down)  == type) { segments[i++] = SOUTH; }
    if (side_getType(t->left)  == type) { segments[i++] = WEST; }
    return segments;
}

void tile_freeSegments(direction** selfPtr) {
    free(*selfPtr);
    *selfPtr = NULL;
}

bool tile_hasCastle(const tile* t) {
    return side_getType(t->up)    == CASTLE
        || side_getType(t->right) == CASTLE
        || side_getType(t->down)  == CASTLE
        || side_getType(t->left)  == CASTLE;
}

bool tile_hasRoad(const tile* t) {
    return side_getType(t->up)    == ROAD
        || side_getType(t->right) == ROAD
        || side_getType(t->down)  == ROAD
        || side_getType(t->left)  == ROAD;
}

bool tile_hasTemple(const tile* t) { return tile_getCenter(t) == TEMPLE; }

bool tile_hasCrossroads(const tile* t) { return tile_getCenter(t) == CROSSROASDS; }

bool tile_hasShield(const tile* t) { return t->mod == SHIELD; }

bool tile_isSymmetric(const tile* t) {
    return t->up->type   == t->down->type
        && t->left->type == t->right->type;
}

bool tile_isUniform(const tile* t) {
    return t->up->type   == t->down->type
        && t->down->type == t->left->type
        && t->left->type == t->right->type;
}
