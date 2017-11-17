#include <assert.h>

#include "datatypes.h"
#include "action.h"
#include "map.h"
#include "input.h"
#include "key.h"

point_t temp_point;

int action_make_move(map_t *map)
{
    point_t point;
    int loop = 1;
    int multiplier = 0;
    input_key_t key;
    int touched;

    /* calculate the update */
    point.x = map -> cursor.x;
    point.y = map -> cursor.y;

    /* get key and check if it's unlocked */
    key = input_get_key();

    while (loop) {

        /* 1 if the real x of cursor is touched and thus has to be changed.
         * a successful change of x by a key can do that */
        touched = 0;

        if (!key_unlocked(key)) {
            key = input_get_key();
            continue;
        } else {
            loop--;
        }

        switch (key) {
            case 'j':
                point.y += 1;
                point.x = map -> real_x;
                break;
            case 'k':
                point.y -= 1;
                point.x = map -> real_x;
                break;
            case 'l':
                point.x += 1;
                touched = 1;
                break;
            case 'h':
                point.x -= 1;
                touched = 1;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                multiplier = (multiplier) * 10 + key - '0';

                /* loop it multiplier number of times */
                loop = multiplier;
                key = input_get_key();
                break;
            case 'q':
                return 0;
        }

        while (point.x && !map_is_free(map, point)) {
            point.x--;

            /* could not update x, thus it was not actually touched */
            touched = 0;
        }

        /* if point is 0, no place to put cursor */
        if (point.x == 0) continue;

        /* if it was touched, update the real x */
        if (touched) map -> real_x = point.x;

        /* update cursor */
        map -> cursor.x = point.x;
        map -> cursor.y = point.y;
    }

    return 1;
}

void action_prompt()
{
    input_get_key();
}
