#include "datatypes.h"

mapfile_data_t map = {
    .size = {
        .y = 3,
        .x = 8,
    },
    .cursor = {
        .y = 1,
        .x = 6,
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
                    .y = 1,
                    .x = 6,
                },
                .value = 'h',
            },
        },
    },
    .data = {
    "++++++++",
    "+     h+",
    "++++++++",
    },
    .story = "When nothing seems right, go left...",
};
