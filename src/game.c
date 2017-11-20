/*
 * src/game.c
 * Define the module for the handling game, help, settings and other
 * options in the menu
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

#include "datatypes.h"
#include "game.h"
#include "interface.h"
#include "action.h"
#include "key.h"
#include "map.h"
#include "msg.h"


game_t game;                    /* Keep the game detail */
char map_name[][3] = {          /* Store the map names */
    "\0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"
};


/* play the game with the details loaded in 'game' */
int play(const map_t*);

/* acquire the contents of the tile and take appropriate actions */
boolean acquire_tile(const map_t *);


void game_play()
{
    int on = 1;
    game.level = 1;
    key_lock_all();
    game.status.score = 0;

    while (on) {
        const map_t *map = map_open(map_name[game.level]);
        if (!map) return;

        on = play(map);

        map_close(map);
        game.level++;
    }
}

void game_help()
{
}

void game_exit()
{
}

int play(const map_t *map)
{
    /* unlock the command mode key */
    key_unlock(':');

    /* show the story */
    interface_display_clear();
    interface_display_prompt(map -> story);

    while (1) {
        interface_display_map(map);
        interface_display_status(game.status);

        /* acquire gems, letters etc from the tile, if a door is reached,
         * get out of the loop */
        if (!acquire_tile(map))
            break;

        command_t command = action_make_move(map);
        if (command.type == COMMAND_QUIT)
            return 0;
    }

    return 1;
}

boolean acquire_tile(const map_t *map)
{
    map_tile_t tile;

    /* get tile details for the map */
    tile = map_get_tile(map -> cursor);

    /* if the cursor got onto a letter tile, unlock it */
    if (tile.type == TILE_LETTER) {
        key_unlock(tile.value);

        /* display a msg */
        interface_display_message(msg_get_keymsg(tile.value));

        /* update the old tile to grass */
        map_take_letter();

    } else if (tile.type == TILE_GEM) {
        /* add score and update status bar */
        game.status.score += 10;
        interface_display_status(game.status);

        /* display a msg */
        interface_display_message("You got a gem!");

        /* update the old tile to grass */
        map_take_gem();

    } else if (tile.type == TILE_DOOR) {

        /* check if all gems are collected */
        if (map -> gems_left) {
            interface_display_message("There are some gems left to collect!");
        } else if (map -> letters_left) {
            interface_display_message("There are some characters you did not unlock!");
        } else {
            interface_display_message("Press any key to continue...");
            interface_input_key();
            return B_FALSE;
        }
    }

    return B_TRUE;
}
