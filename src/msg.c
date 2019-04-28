/*
 * src/msg.c
 * Define the module for getting the messages for keys
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
#include <stdlib.h>             /* for NULL */

#include "datatypes.h"
#include "msg.h"

#define MAX_MSG_SIZE 100
#define START 32                /* the first key character */


/* store the unlock messages for each key */
char message[KEY_MAX_SIZE - START][MAX_MSG_SIZE] = {
    /* start from START ie 'space' */
    "You unlocked 'space'",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "You unlocked 0.",
    "You unlocked 1.",
    "You unlocked 2.",
    "You unlocked 3.",
    "You unlocked 4.",
    "You unlocked 5.",
    "You unlocked 6.",
    "You unlocked 7.",
    "You unlocked 8.",
    "You unlocked 9.",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked A.",
    "You unlocked Z.",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked h.",
    "You unlocked a.",
    "You unlocked j.",
    "You unlocked k.",
    "You unlocked l.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked a.",
    "You unlocked z.",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
};

char * msg_get_keymsg(input_key_t key)
{
    if (key - START < 0 || key > KEY_MAX_SIZE) {
        return NULL;
    }
    return message[key - START];
}
