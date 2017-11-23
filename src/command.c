/*
 * src/command.c
 * Defile the module for taking and executing commands
 *
 * Copyright (C) 2017 Utkarsh Mahshwari <utkarshme96@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>             /* for malloc(), NULL */
#include <string.h>             /* for strcmp() */
#include <ctype.h>              /* for isalnum() */

#include "datatypes.h"
#include "command.h"
#include "interface.h"
#include "map.h"


void increment_cursor(const map_t *map, point_t *point)
{
    point -> x++;
    if (point -> x >= map -> size.x) {
        point -> x = 1;
        point -> y++;
    }
    if (point -> y >= map -> size.y) {
        point -> x = 0;
        point -> y = 0;
    }
}

int get_count()
{
    int count = 0;

    while (1) {
        input_key_t key = interface_input_key();

        /* if first key for count is zero, then it is be the '0' motion key */
        if (count == 0 && key == '0') {
            interface_input_key_undo(key);
            return 1;

        /* if key is a number add it */
        } else if (key >= '0' && key <= '9') {
            count = count * 10 + (key - '0');

        /* if key is not a number, it is a command */
        } else {
            interface_input_key_undo(key);
            if (!count) count = 1;
            break;
        }
    }

    return count;
}

int get_oper()
{
    input_key_t key = interface_input_key();
    switch (key) {
        case 'd':
        case 'c':
        case 'y':
            return key;
        default:
            interface_input_key_undo(key);
            return 0;
    }
}

int get_motion()
{
    input_key_t key = interface_input_key();
    return key;
}

point_t * exec_motion(const map_t *map, const command_t *command)
{
    point_t temp = { .y = map -> cursor.y, .x = map -> real_x };
    map_tile_t tile;
    int flag1 = 0;
    int flag2 = 1;

    switch (command -> motion.value) {
        case 'j':
            temp.y += 1;
            break;
        case 'k':
            temp.y -= 1;
            break;
        case 'l':
            temp.x = map -> cursor.x + 1;
            break;
        case 'h':
            temp.x = map -> cursor.x - 1;
            break;

        case 'w':
            tile = map_get_tile(temp);
            if (tile.type != TILE_TEXT) break;

            /* how: at the start, flag is the 1 if the current tile is
             * alphanumeric. we keep incrementing cursor till an opposite
             * value is found. but if we encounter space between incrementing
             * any non-space value is the stop point */
            flag1 = isalnum(tile.value);
            flag2 = 0;          /* when any non-space works, it's 1 */
            while (1) {
                if ((flag1 != isalnum(tile.value) || flag2)
                        && tile.value != ' ')
                    break;

                increment_cursor(map, &temp);
                /* temp becomes (0, 0) if end of map */
                if (temp.x == 0 && temp.y == 0) break;
                tile = map_get_tile(temp);

                if (tile.value == ' ') flag2 = 1;
            }
            break;
    }

    if (temp.y == map -> cursor.y && !map_is_free(temp)) {
        return NULL;
    }

    while (temp.y != map -> cursor.y && temp.x && !map_is_free(temp))
        temp.x--;

    if (map_is_free(temp)) {
        point_t *point = (point_t *) malloc(sizeof(point_t));
        point -> y = temp.y;
        point -> x = temp.x;
        return point;

    } else {
        return NULL;
    }
}

command_t * get_command_line()
{
    command_t *command = NULL;
    char *line;

    input_key_t key = interface_input_key();
    if (key != ':') {
        interface_input_key_undo(key);
        return NULL;
    }

    command = (command_t *) malloc(sizeof(command_t));
    line = interface_input_command();
    if (line == NULL) {
        return 0;
    }

    if (!strcmp(line, "quit") || !strcmp(line, "q")) {
        command -> type = COMMAND_QUIT;
        interface_display_command("quit");

    } else if (!strcmp(line, "help") || !strcmp(line, "h")) {
        command -> type = COMMAND_HELP;
        interface_display_command("help");

    } else {
        command -> type = COMMAND_NOP;
        interface_display_command("command not found");
    }

    free(line);
    return command;
}

command_t * command_get()
{
    command_t *command;

    /* check if it's a command line */
    if ((command = get_command_line()) != NULL)
        return command;

    /* else build the command */
    command = (command_t *) malloc(sizeof(command_t));
    command -> type         = COMMAND_OTHER;
    command -> count        = get_count();
    command -> oper         = get_oper();
    if (command -> oper == 0) {
        command -> motion.count = command -> count;
        command -> count = 1;
    } else {
        command -> motion.count = get_count();
    }
    command -> motion.value = get_motion();

    return command;
}

void command_exec(const map_t *map, const command_t *command)
{
    int count = command -> count;

    if (command -> type == COMMAND_NOP) {
        return;
    }

    while (count--) {

        int count2 = command -> motion.count;
        while (count2--) {

            point_t *end = exec_motion(map, command);
            if (end) {
                /* the real x value is not updated on using the j & k keys */
                if (command -> motion.value != 'j'
                        && command -> motion.value != 'k') {
                    map_set_cursor(*end);
                    map_set_real_cursor();
                }
                map_set_cursor(*end);
                free(end);
            }
        }
    }
}
