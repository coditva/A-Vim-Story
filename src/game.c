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
int play();

/* acquire the contents of the tile and take appropriate actions */
boolean acquire_tile(map_t *);


void game_play()
{
    game.level = 1;
    game.status.score = 0;
    while (play()) {
        game.level++;
    }
}

void game_help()
{
}

void game_exit()
{
}

int play()
{
    map_t *map;

    if (!(map = map_open(map_name[game.level]))) return 0;

    /* unlock the quit key */
    key_unlock('q');

    /* show the story */
    interface_display_clear();
    interface_display_prompt(map -> story);

    while (1) {
        interface_display_map(map);
        interface_display_status(game.status);

        if (!acquire_tile(map))
            return 1;

        if (!action_make_move(map))
            return 0;
    }

    map_close();
    return 1;
}

boolean acquire_tile(map_t *map)
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
        tile.type = TILE_GRASS;
        tile.value = ' ';
        map_set_tile(map -> cursor, tile);
        map -> chars_left--;

    } else if (tile.type == TILE_GEM) {
        /* add score and update status bar */
        game.status.score += 10;
        interface_display_status(game.status);

        /* update the old tile to grass */
        tile.type = TILE_GRASS;
        map_set_tile(map -> cursor, tile);
        map -> gems_left--;

        /* display a msg */
        interface_display_message("You got a gem!");

    } else if (tile.type == TILE_DOOR) {

        /* check if all gems are collected */
        if (map -> gems_left) {
            interface_display_message("There are some gems left to collect!");
        } else if (map -> chars_left) {
            interface_display_message("There are some characters you did not unlock!");
        } else {
            interface_display_message("Press any key to continue...");
            action_prompt();
            return B_FALSE;
        }
    }

    return B_TRUE;
}
