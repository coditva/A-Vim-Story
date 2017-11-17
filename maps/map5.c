#include "datatypes.h"

mapfile_data_t map = {
    .size = {
        .y = 8,
        .x = 29,
    },
    .cursor = {
        .y = 1,
        .x = 1,
    },
    .exit = {
        .y = 7,
        .x = 28,
    },
    .gems = {
        .count = 7,
        .data = {
            {
                .y = 1,
                .x = 20,
            },
            {
                .y = 3,
                .x = 10,
            },
            {
                .y = 3,
                .x = 12,
            },
            {
                .y = 5,
                .x = 12,
            },
            {
                .y = 5,
                .x = 14,
            },
            {
                .y = 7,
                .x = 14,
            },
            {
                .y = 7,
                .x = 16,
            },
        },
    },
    .data = {
        "++++++++++++++++++++++++++++++",
        "+                   ++++++++++",
        "+ ++++++++++++++++++++++++++++",
        "+          +             +++++",
        "+ ++++++++++++++++++++++++++++",
        "+            +         +++++++",
        "+ ++++++++++++++++++++++++++++",
        "+              +       +     +",
        "+ ++++++++++++++++++++++++++++",
    },
    .story = "There are times when you must give up your position to advance in life. But one must remember one's real position...",
};
