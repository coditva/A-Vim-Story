/*
 * src/menu.c
 * Define the module for handling the menu in the game
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

#include <ncurses.h>            /* for key names */

#include "datatypes.h"
#include "menu.h"
#include "interface.h"


enum menu_item menu_display()
{
    input_key_t key;
    enum menu_item choice = MENU_NEW_GAME;

    interface_display_menu(MENU_NEW_GAME);

    while (1) {
        key = interface_input_key();

        if (key == 10) {
            break;
        }

        switch (key) {
            case 'j':
            case KEY_DOWN:
                choice++;
                if (choice == MENU_SIZE) choice = 0;
                break;
            case 'k':
            case KEY_UP:
                if (choice == 0) choice = MENU_SIZE;
                choice--;
                break;
            default:
                continue;
        }


        interface_display_menu(choice);
    }

    return choice;
}
