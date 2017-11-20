/*
 * src/main.c
 * The entry point of the application
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

#include <signal.h>             /* for signal() */
#include <stdlib.h>             /* for exit() */

#include "datatypes.h"
#include "game.h"
#include "interface.h"
#include "menu.h"

void signal_handler(int);

int main(int argc, char *argv[])
{
    enum menu_item choice = -1;

    /* attach handler to signals */
    signal(SIGINT , signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGSTOP, signal_handler);

    interface_init();

    while (1) {
        choice = menu_display();

        if (choice == MENU_NEW_GAME) {
            game_play();
        } else if (choice == MENU_HELP) {
            game_help();        /* display help msg */
        } else if (choice == MENU_QUIT) {
            game_exit();
            break;              /* exit the loop */
        }
    }

    /* cleanup everything */
    interface_destroy();

    return 0;
}

void signal_handler(int signal_number)
{
    interface_destroy();
    exit(1);
}
