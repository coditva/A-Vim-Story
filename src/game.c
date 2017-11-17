#include <assert.h>
#include <stdlib.h>             /* for NULL */
#include <string.h>             /* for strcpy() */

#include "datatypes.h"
#include "game.h"
#include "action.h"
#include "key.h"
#include "display.h"
#include "map.h"
#include "msg.h"

/* Keep the game detail */
game_t game;
void prompt(char *message);
char map_name[][3] = {
    "0", "1", "2", "3", "4", "5", "6", "7",
};

int play();

void game_play()
{
    game.level = 0;
    game.status.score = 0;
    while (play()) {
        game.level++;
    }
}

int play()
{
    map_t *map = NULL;
    map_tile_t tile;

    if (!(map = map_load(map_name[game.level]))) return 0;
    assert(map);

    /* unlock the quit key */
    key_unlock('q');

    /* show the story */
    prompt(map -> story);

    while (1) {
        display_map_show(map);
        display_status_show(game.status);

        /* get tile details for the map */
        tile = map_get_tile(map, map -> cursor);

        /* if the cursor got onto a letter tile, unlock it */
        if (tile.type == TILE_LETTER) {
            key_unlock(tile.value);

            /* display a msg */
            display_msg_show(msg_get_keymsg(tile.value));

        } else if (tile.type == TILE_GEM) {
            /* add score and update status bar */
            game.status.score += 10;
            display_status_show(game.status);

            /* update the old tile to grass */
            tile.type = TILE_GRASS;
            map_set_tile(map, map -> cursor, tile);
            map -> gems_left--;

            /* display a msg */
            display_msg_show("You got a gem!");

        } else if (tile.type == TILE_DOOR) {

            /* check if all gems are collected */
            if (map -> gems_left) {
                display_msg_show("There are some gems left to collect!");
            } else {
                display_msg_show("Press any key to continue...");
                action_prompt();
                break;
            }
        }

        if (!action_make_move(map))
            return 0;
    }

    map_free(map);
    return 1;
}

void prompt(char *message)
{
    display_clear();
    display_prompt_show(message);
    action_prompt();
}
