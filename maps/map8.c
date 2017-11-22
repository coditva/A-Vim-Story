#include "datatypes.h"

mapfile_data_t map = {

    /* size indexed from 0 */
    .size = {
        .y = 2,
        .x = 109,
    },

    /* cursor indexed from 0 */
    .cursor = {
        .y = 1,
        .x = 1,
    },

    /* exit indexed from 0 */
    .exit = {
        .y = 1,
        .x = 97,
    },

    /* number of gems stored in the map and their locations */
    .gems = {

        /* the number of gems in the map */
        .count = 4,

        /* indexed from 0 */
        .data = {
            {
                .y = 1,
                .x = 14,
            },
            {
                .y = 1,
                .x = 34,
            },
            {
                .y = 1,
                .x = 44,
            },
            {
                .y = 1,
                .x = 77,
            },
        },
    },
    .letters = {
        .count = 9,
        .data = {
            {
                .point = {
                    .y = 1,
                    .x = 3,
                },
                .value = '1',
            },
            {
                .point = {
                    .y = 1,
                    .x = 10,
                },
                .value = '2',
            },
            {
                .point = {
                    .y = 1,
                    .x = 16,
                },
                .value = '3',
            },
            {
                .point = {
                    .y = 1,
                    .x = 21,
                },
                .value = '4',
            },
            {
                .point = {
                    .y = 1,
                    .x = 27,
                },
                .value = '5',
            },
            {
                .point = {
                    .y = 1,
                    .x = 36,
                },
                .value = '6',
            },
            {
                .point = {
                    .y = 1,
                    .x = 46,
                },
                .value = '7',
            },
            {
                .point = {
                    .y = 1,
                    .x = 55,
                },
                .value = '8',
            },
            {
                .point = {
                    .y = 1,
                    .x = 65,
                },
                .value = '9',
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
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
        "+  1 ++++ 2 +   3 ++ 4 +++ 5 ++++   6 +++++   7 ++++++ 8 +++++++ 9 +++++++++    +++++++++++++++   ++++++++++++",
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
    },

    /* a piece of story shown before proceding to the level */
    .story = "Repeating a thing is nice. Repeating a thing in the correct way is better...",
};
