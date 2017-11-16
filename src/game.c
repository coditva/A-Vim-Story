#include <assert.h>

#include "datatypes.h"
#include "game.h"
#include "action.h"
#include "score.h"
#include "key.h"
#include "display.h"
#include "map.h"
#include "msg.h"

int game_play(game_t game)
{
    map_t *map = game.map;
    map_tile_t tile;

    /* init game vars */
    score_update(0);

    assert(map);

    /* unlock the basic keys */
    key_unlock('q');
    key_unlock('h');
    key_unlock('j');
    key_unlock('k');
    key_unlock('l');

    while (1) {
        display_map_show(map);
        display_status_show();

        /* get tile details for the map */
        tile = map_get_tile(map, map -> cursor);

        /* if the cursor got onto a letter tile, unlock it */
        if (tile.type == TILE_LETTER) {
            key_unlock(tile.value);

            /* display a msg */
            display_msg_show(msg_get_keymsg(tile.value));

        } else if (tile.type == TILE_GEM) {
            /* add score and update status bar */
            score_add(10);
            display_status_show();

            /* update the old tile to grass */
            tile.type = TILE_GRASS;
            map_set_tile(map, map -> cursor, tile);

            /* display a msg */
            display_msg_show("You got a gem!");

        } else if (tile.type == TILE_DOOR) {
            /* add score and update status bar */
            score_add(20);
            display_status_show();

            /* display a msg */
            display_msg_show("You reached a door and won the game!");
        }

        if (!action_make_move(map))
            break;
    }
    return B_TRUE;
}
