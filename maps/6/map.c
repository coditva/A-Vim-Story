#include "datatypes.h"

mapfile_data_t map = {
    .size = {
        .y = 5,
        .x = 19,
    },
    .cursor = {
        .y = 1,
        .x = 1,
    },
    .exit = {
        .y = 4,
        .x = 18,
    },
    .gems = {
        .count = 5,
        .data = {
            {
                .y = 3,
                .x = 1,
            },
            {
                .y = 4,
                .x = 6,
            },
            {
                .y = 1,
                .x = 7,
            },
            {
                .y = 1,
                .x = 18,
            },
            {
                .y = 4,
                .x = 10,
            },
        },
    },
    .data = {
       //012345678901234567890
        "++++++++++++++++++++",
        "+   +++ ++++    ++ +",
        "+++          ++    +",
        "+ + + ++ + +   +++++",
        "+   +  + +   +     +",
        "++++++++++++++++++++",
    },
    .story = "No matter the obstacles, do what must be done...",
};
