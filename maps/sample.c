#include "datatypes.h"

mapfile_data_t map = {

    /* size indexed from 0 */
    .size = {
        .y = 0,
        .x = 0,
    },

    /* cursor indexed from 0 */
    .cursor = {
        .y = 0,
        .x = 0,
    },

    /* exit indexed from 0 */
    .exit = {
        .y = 0,
        .x = 0,
    },

    /* number of gems stored in the map and their locations */
    .gems = {

        /* the number of gems in the map */
        .count = 1,

        /* indexed from 0 */
        .data = {
            {
                .y = 0,
                .x = 0,
            },
        },
    },

    /* the map data which describes the paths in the map
     * the available characters for the same are:
     * '+' : to denote an obstacle or boundary tile
     * ' ' : to denote a walkable tile
     * '-' : to denote the space character
     * 'j' : to denote a 'j' alphabet, etc. */
    .data = {
        "",
    },

    /* a piece of story shown before proceding to the level */
    .story = "A piece of story...",
};
