#include "datatypes.h"

mapfile_data_t map = {
    .size = {
        .y = 8,
        .x = 3,
    },
    .cursor = {
        .y = 1,
        .x = 1,
    },
    .exit = {
        .y = 6,
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
                    .x = 1,
                },
                .value = 'j',
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
        "+ +",
        "+++",
    },
    .story = "In the land of our hero, all was peaceful and quiet until the evil lord took over everything. Now our hero must defeat him and restore the peace!\n\n\nBut before he can conquer the world, he must learn to walk...",
};
