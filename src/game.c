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
char map_name[][3] = {
    "\0", "1", "2", "3", "4", "5", "6", "7",
};

void game_level_increment();


boolean game_init()
{
    game.level = 1;
    game.status.score = 0;
    return B_TRUE;
}

int game_play()
{
    map_t *map = NULL;
    map_tile_t tile;

    if (!(map = map_load(map_name[game.level]))) return B_FALSE;
    assert(map);

    /* unlock the basic keys */
    key_unlock('q');
    key_unlock('h');
    key_unlock('j');
    key_unlock('k');
    key_unlock('l');

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

            /* display a msg */
            display_msg_show("You got a gem!");

        } else if (tile.type == TILE_DOOR) {
            /* add score and update status bar */
            game.status.score += 20;
            display_status_show(game.status);
            break;
        }

        if (!action_make_move(map))
            return B_FALSE;
    }

    map_free(map);

    /* prompt user to procede */
    display_msg_show("You reached a door and won the game! Press any key to continue");
    game.level++;
    action_prompt();

    return B_TRUE;
}
