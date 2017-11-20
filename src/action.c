#include <assert.h>             /* for assert() */
#include <string.h>             /* for strcmp(), strcat() */
#include <stdlib.h>             /* for free() */

#include "datatypes.h"
#include "action.h"
#include "map.h"
#include "interface.h"
#include "key.h"


command_t input_command();


command_t action_make_move(const map_t *map)
{
    point_t point;
    int loop = 1;
    int multiplier = 0;
    input_key_t key;
    int touched;
    command_t command;

    /* calculate the update */
    point.x = map -> cursor.x;
    point.y = map -> cursor.y;

    /* get key and check if it's unlocked */
    key = interface_input_key();

    while (loop) {

        /* 1 if the real x of cursor is touched and thus has to be changed.
         * a successful change of x by a key can do that */
        touched = 0;

        if (!key_unlocked(key)) {
            key = interface_input_key();
            continue;
        } else {
            loop--;
        }

        switch (key) {
            case 'j':
                point.y += 1;
                point.x = map -> real_x;
                command.type = COMMAND_MOTION;
                break;
            case 'k':
                point.y -= 1;
                point.x = map -> real_x;
                command.type = COMMAND_MOTION;
                break;
            case 'l':
                point.x += 1;
                touched = 1;
                command.type = COMMAND_MOTION;
                break;
            case 'h':
                point.x -= 1;
                touched = 1;
                command.type = COMMAND_MOTION;
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
                key = interface_input_key();
                break;

            case ':':
                return input_command();
        }

        /* if the point is out of bounds, illegal move */
        if (point.y >= map -> size.y || point.x >= map -> size.x) {
            continue;
        }

        /* if the line was not changed and the tile is not free, invalid move */
        if (point.y == map -> cursor.y && !map_is_free(point)) {
            continue;
        }

        /* if line was changed and we can find a point which is before the
         * desired point, move to it */
        while (point.x && !map_is_free(point)) {
            point.x--;
        }

        /* if point is 0, no place to put cursor, invalid move */
        if (point.x == 0) continue;

        /* update cursor */
        map_set_cursor(point);

        /* if x was touched, this is now the real x */
        if (touched) map_set_real_cursor();
    }

    return command;
}

command_t input_command()
{
    command_t command;
    char *line;

    line = interface_input_command();

    if (!strcmp(line, "quit") || !strcmp(line, "q")) {
        command.type = COMMAND_QUIT;
        interface_display_command("quit");

    } else if (!strcmp(line, "help") || !strcmp(line, "h")) {
        command.type = COMMAND_HELP;
        interface_display_command("help");

    } else {
        command.type = COMMAND_NOP;
        interface_display_command("command not found");
    }

    free(line);
    return command;
}
