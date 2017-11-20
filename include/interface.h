/*
 * include/interface.h
 * Declare the interface for handling the display and input
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

#ifndef INTERFACE_H_N7LPPW8B
#define INTERFACE_H_N7LPPW8B


/**
 * Initialize the display
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean interface_init();


/**
 * Destroy the display and clear all allocated space
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean interface_destroy();


/**
 * Clear and refresh the whole display
 */
void interface_display_clear();


/**
 * Refreshes and shows the menu on top of all windows
 * @param The item to show as selected
 */
void interface_display_menu(enum menu_item);


/**
 * Refreshes and shows the menu on top of all windows
 * @param The item to show as selected
 */
void interface_display_map(const map_t *);


/**
 * Show the given message in a status bar at the bottom
 * @param The message to show
 */
void interface_display_command(char *command);


/**
 * Show the given message in a popup msg window
 * @param The message to show
 */
void interface_display_message(char *);


/**
 * Show a prompt window with the given message
 * @param The message to show
 */
void interface_display_prompt(char *);


/**
 * Show the status bar
 */
void interface_display_status(game_status_t);


/**
 * Wait for a key press and return it
 * @return The key pressed
 */
input_key_t interface_input_key();


/**
 * Keep taking input till the user presses enter
 * @return The line terminated by '\0'
 */
char * interface_input_command();


#endif /* end of include guard: INTERFACE_H_N7LPPW8B */
