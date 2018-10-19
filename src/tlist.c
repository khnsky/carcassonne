#include "tlist.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool tlist_parse(const char* filename, sized_tlist* list) {
    if (!list || !list->tiles) { return false; }
    TRY(FILE* file, (file = fopen(filename, "r")), return 0);
    for (size_t i = 0; i < list->size; ++i) {
        // if any tile parsing fails return false
        if (!tile_parse(file, &list->tiles[i])) {
            fclose(file);
            return false;
        }
    }
    fclose(file);
    return true;
}

size_t tlist_get_len(const char* filename) {
    FILE* list = fopen(filename, "r");
    size_t count = 0;
    if (list) {
        int ch;
        while ((ch = getc(list)) != EOF) {
            while ((ch = getc(list)) != EOF && isspace(ch)) { ; }
            if (ch != EOF && !isspace(ch)) { count++; }
            while ((ch = getc(list)) != EOF && !isspace(ch)) { ; }
        }
        fclose(list);
    }
    return count;
}

bool tlist_init(const char* filename, sized_tlist* list) {
    *list = (sized_tlist) {
        .size  = tlist_get_len(filename),
        .tiles = calloc(list->size, sizeof(tile*)),
    };
    return tlist_parse(filename, list);
}

sized_tlist tlist_init_exit_on_err(const char* filename) {
    sized_tlist list;
    if (!tlist_init(filename, &list)) {
        free(list.tiles);
        fputs("error parsing tile list\n", stderr);
        exit(EXIT_FAILURE);
    }
    return list;
}

void tlist_free(sized_tlist* list) {
    for (size_t i = 0; i < list->size; ++i) {
        tile_free(list->tiles[i]);
        free(list->tiles[i]);
        list->tiles[i] = NULL;
    }
    free(list->tiles);
    list->tiles = NULL;
}


void tlist_print(const sized_tlist* list) {
    int counter = 1;                                    // separate counter for display
    for (size_t i = 0; i < list->size; ++i) {
        if (list->tiles[i]) {                           // if tile nonempty
            printf("%-3d: ", counter);
            tile_print(list->tiles[i]);
            putchar('\n');
            counter++;
        }
    }
}

bool tlist_write(const sized_tlist* list, const char* filename) {
    TRY(FILE* file, (file = fopen(filename, "w")), return 0);
    char str[5];
    for (size_t i = 0; i < list->size; ++i) {
        fprintf(file, "%.*s\n", 5, tile_to_str(list->tiles[i], str));
    }
    fclose(file);
    return true;
}

tile* tlist_eraseAt(sized_tlist* list, size_t index) {
    if(index >= list->size) { return NULL; }
    tile* t = list->tiles[index];
    for(size_t i = index; i < list->size - 1; ++i) {
        list->tiles[i] = list->tiles[i + 1];
    }
    list->size--;
    return t;
}
