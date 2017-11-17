#include "datatypes.h"

mapfile_data_t map = {
    .size = {
        .y = 13,
        .x = 46,
    },
    .cursor = {
        .y = 2,
        .x = 10,
    },
    .exit = {
        .y = 2,
        .x = 10,
    },
    .gems = {
        .count = 0,
    },
    .data = {
        "+++++++++++++++++++++++++++++++++++++++++++++",
        "+                                           +",
        "+ You-are---.                               +",
        "+                                           +",
        "+ The-objective-is-to-reach-a-yellow-'door' +",
        "+ after-collecting-all-the-gems.            +",
        "+                                           +",
        "+ Unlock-'keys'-(by-going-over-them)-to-use +",
        "+ them-for-moving-around.                   +",
        "+                                           +",
        "+ Complete-each-task-in-least-number-of-key +",
        "+ strokes-to-score-higher.                  +",
        "+                                           +",
        "+++++++++++++++++++++++++++++++++++++++++++++",
    },
    .story = "In the land of out hero, all was peaceful and quiet until the evil lord conquered everything. Now, our hero must defeat the evil lord and restore the peace!",
};
