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
    char buffer[18][82] = {
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#############################################~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#              #   #            #           #~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# ############ # # # ######## # # ######### #~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# #            # # # #   #  # # #   # # #   #~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# ################ # # #   ## # # # #   # # #~+",
        "+~       #   #                                        # # ###### # # # ## ## # #~+",
        "+~       # # # ~~~~~~~~~~~~~~~~~~~~##################   #        # # #       # #~+",
        "+~       # # # ~~~~~~~~~~~~~~~~~~~~#                  ############ # ######### #~+",
        "+~         #   ~~~~~~~~~~~~~~~~~~~~# ############# ###   #   #     #           #~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# #           #   # # # #   ########## ######~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# # ######### ### ### #  # #       #         ~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# ########### #   #    # # ##### # # ########~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#             # ### ## # # #   # # #    #   #~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~###############      #   #   #   #   ##   #  ~+",
        "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+",
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
    };

    map = (map_t *) malloc(sizeof(map_t));

    map -> size.x = 82;
    map -> size.y = 18;

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
                case '+':
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

    map -> cursor.x = 4;
    map -> cursor.y = 8;

    return map;
}

boolean map_is_free(map_t *map, point_t point)
{
    int pos = 0;

    pos = map -> size.x * point.y + point.x;
    if (map -> data[pos] == TILE_GRASS) {
        return B_TRUE;
    }
    return B_FALSE;
}
