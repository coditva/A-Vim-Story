#include "datatypes.h"

mapfile_data_t map = {
    .size = {
        .y = 8,
        .x = 3,
    },
    .cursor = {
        .y = 6,
        .x = 1,
    },
    .exit = {
        .y = 1,
        .x = 1,
    },
    .gems = {
        .count = 0,
    },
    .letters = {
        .count = 1,
        .data = {
            {
                .point = {
                    .y = 6,
                    .x = 1,
                },
                .value = 'k',
            },
        },
    },
    .data = {
        "+++",
        "+ +",
        "+ +",
        "+ +",
        "+ +",
        "+ +",
        "+k+",
        "+++",
    },
    .story = "Once you know how to go down, you can go up...",
};
