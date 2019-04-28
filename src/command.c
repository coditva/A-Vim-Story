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
#include "key.h"


int get_motion()
{
    input_key_t key = interface_input_key();

    if (!key_unlocked(key)) {
        return 0;
    }
    return key;
}


int command_exec(const map_t *map)
{
    input_key_t key;
    while (1) {
        key = interface_input_key();
        if (key_unlocked(key)) {
            break;
        }
    }

    /* send key to neovim */

    /* get screen state */

    /* parse screen state */

    /* update map */

    return 1;
}
