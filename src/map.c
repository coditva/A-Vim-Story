#include <unistd.h>             /* for NULL */
#include <stdlib.h>             /* for malloc() */
#include <assert.h>             /* for assert() */

#include "datatypes.h"
#include "map.h"

boolean map_init()
{
    return B_TRUE;
}

map_t * map_load()
{
    /* TODO: remove the hardcoded map */

    map_t *map = NULL;
    char buffer[10][10] = {
        "**********",
        "* # #    *",
        "* # # ~~ *",
        "*     ~~ *",
        "* ####   *",
        "* ####   *",
        "*     ~~ *",
        "* # # ~~ *",
        "* # #    *",
        "**********"
    };

    map = (map_t *) malloc(sizeof(map_t));

    map -> size.x = 10;
    map -> size.y = 10;

    map -> data = (map_tile_t *) malloc(sizeof(map_tile_t) 
            * map -> size.x
            * map -> size.y);

    int count = 0;
    for (int i = 0; i < map -> size.y; ++i) {
        for (int j = 0; j < map -> size.x; ++j) {
            switch (buffer[i][j]) {
                case '~':
                    map -> data[count] = TILE_WATER;
                    break;
                case '*':
                    map -> data[count] = TILE_BORDER;
                    break;
                case ' ':
                    map -> data[count] = TILE_GRASS;
                    break;
                case '#':
                    map -> data[count] = TILE_BRICK;
                    break;
                default:
                    assert(0);      /* this should never happen */
            }
            count++;
        }
    }

    map -> cursor.x = 1;
    map -> cursor.y = 1;

    return map;
}
