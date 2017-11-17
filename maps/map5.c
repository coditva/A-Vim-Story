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
       //0123456789012345678901234567890
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
    .story = "Sometimes, to make the right move, one must forget the logic and trust one's instincts\n\nWhen something feels absurd but the heart feels it to be true, let go of the fear and do it...",
};
