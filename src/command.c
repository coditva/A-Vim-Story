#include <stdlib.h>             /* for malloc(), NULL */
#include <string.h>             /* for strcmp() */

#include "datatypes.h"
#include "command.h"
#include "interface.h"
#include "map.h"

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

    command = (command_t *) malloc(sizeof(command));
    line = interface_input_command();

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
    command = (command_t *) malloc(sizeof(command));
    command -> type         = COMMAND_OTHER;
    command -> count        = get_count();
    command -> oper         = get_oper();
    command -> motion.count = get_count();
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
                if (end -> y == map -> cursor.y
                        && end -> x != map -> cursor.x) {
                    map_set_cursor(*end);
                    map_set_real_cursor();
                }
                map_set_cursor(*end);
                free(end);
            }
        }
    }
}
