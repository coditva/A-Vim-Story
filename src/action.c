#include "datatypes.h"
#include "action.h"
#include "map.h"

void action_make_move(map_t *map, input_key_t key)
{
    point_t point;

    /* check if key's available */

    /* calculate the update */
    point.x = map -> cursor.x;
    point.y = map -> cursor.y;
    switch (key) {
        case 'j':
            point.y = map -> cursor.y + 1;
            break;
        case 'k':
            point.y = map -> cursor.y - 1;
            break;
        case 'l':
            point.x = map -> cursor.x + 1;
            break;
        case 'h':
            point.x = map -> cursor.x - 1;
            break;
    }

    /* check if map is free and update the map */
    if (map_is_free(map, point)) {
        map -> cursor.x = point.x;
        map -> cursor.y = point.y;
    }
}
