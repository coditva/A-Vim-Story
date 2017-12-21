#include "datatypes.h"

mapfile_data_t map = {

    /* size indexed from 0 */
    .size = {
        .y = 4,
        .x = 32,
    },

    /* cursor indexed from 0 */
    .cursor = {
        .y = 1,
        .x = 1,
    },

    /* exit indexed from 0 */
    .exit = {
        .y = 0,
        .x = 30,
    },

    /* number of gems stored in the map and their locations */
    .gems = {

        /* the number of gems in the map */
        .count = 0,
    },

    /* the number of letters in the map and their location, value */
    .letters = {

        /* the number of letters */
        .count = 0,
    },

    /* the map data which describes the paths in the map
     * the available characters for the same are:
     * '+' : to denote an obstacle or boundary tile
     * ' ' : to denote a walkable tile
     * '-' : to denote the space character
     * 'j' : to denote a 'j' alphabet, etc. */
    .data = {
        "+++++++++++++++++++++++++++++++++",
        "+ --th.s-is---th.s-is---th.s-is-+",
        "+-t!?s-is-fut!?s-is-fut!?s-is-fu+",
        "+eah-!eah-yeah-yeah-yeah-yeah-ye+",
        "+++++++++++++++++++++++++++++++++",
    },

    /* a piece of story shown before proceding to the level */
    .story = "A piece of story...",
};
