#include <stdlib.h>             /* for malloc() */
#include <assert.h>             /* for assert() */
#include "datatypes.h"

/* The map! */
#define X 3
#define Y 8
char buffer[Y][X] = {
    "~~~",
    "~j~",
    "~ ~",
    "~ ~",
    "~ ~",
    "~ ~",
    "~%~",
    "~~~"
};

map_t * get_map()
{
    int count = 0;
    map_t *map = (map_t *) malloc(sizeof(map_t));
    assert(map);

    map -> size.y = Y;
    map -> size.x = X;
    map -> cursor.y = 1;
    map -> cursor.x = 1;

    map -> data = (map_tile_t *) malloc(sizeof(map_tile_t) * X * Y);
    assert(map -> data);

    for (int i = 0; i < map -> size.y; ++i) {
        for (int j = 0; j < map -> size.x; ++j) {

            map -> data[count].value = ' ';
            switch (buffer[i][j]) {
                case '~':
                    map -> data[count].type = TILE_WATER;
                    break;
                case ' ':
                    map -> data[count].type = TILE_GRASS;
                    break;
                case '#':
                    map -> data[count].type = TILE_BRICK;
                    break;
                case '%':
                    map -> data[count].type = TILE_DOOR;
                    break;
                case '@':
                    map -> data[count].type = TILE_GEM;
                    break;
                default:
                    map -> data[count].type = TILE_LETTER;
                    map -> data[count].value = buffer[i][j];
            }

            count++;
        }
    }

    return map;
}
