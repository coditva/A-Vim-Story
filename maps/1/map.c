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
    .data = {
        "+++",
        "+j+",
        "+ +",
        "+ +",
        "+ +",
        "+ +",
        "+ +",
        "+++",
    },
    .story = "Before our hero can conquer the world, he must learn to walk! Remember, collect all the gems and reach the door.",
};
