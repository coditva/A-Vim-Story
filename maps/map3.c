#include "datatypes.h"

mapfile_data_t map = {
    .size = {
        .y = 3,
        .x = 8,
    },
    .cursor = {
        .y = 1,
        .x = 1,
    },
    .exit = {
        .y = 1,
        .x = 6,
    },
    .gems = {
        .count = 0,
    },
    .letters = {
        .count = 1,
        .data = {
            {
                .point = {
                    .y = 1,
                    .x = 1,
                },
                .value = 'l',
            },
        },
    },
    .data = {
    "++++++++",
    "+l     +",
    "++++++++",
    },
    .story = "You may want to go up but you must learn to be right and go right.",
};
