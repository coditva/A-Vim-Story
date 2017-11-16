#include <unistd.h>             /* for sleep() */


#include "datatypes.h"
#include "map.h"
#include "display.h"
#include "input.h"
#include "action.h"
#include "key.h"
#include "msg.h"


/* Displays menu on top of everything and gets the user choice */
enum menu_item get_menu_choice();

/* Play the game */
boolean game_play();


int main(int argc, char *argv[])
{
    enum menu_item choice = -1;

    display_init();
    input_init();
    msg_init();

    while (1) {
        choice = get_menu_choice();

        if (choice == MENU_NEW_GAME) {
            game_play();        /* start a new game */
        } else if (choice == MENU_HELP) {
            /* display help msg */
        } else if (choice == MENU_QUIT) {
            break;              /* exit the controller loop */
        }
    }

    display_destroy();
    return 0;
}

enum menu_item get_menu_choice()
{
    input_key_t key;
    enum menu_item choice = MENU_NEW_GAME;

    display_menu_show(MENU_NEW_GAME);

    while (1) {
        key = input_get_key();

        if (key == 10) {
            break;
        }

        switch (key) {
            case 'j':
                choice++;
                break;
            case 'k':
                choice--;
                break;
            default:
                continue;
        }

        if (choice == MENU_SIZE) choice = 0;
        if (choice == -1) choice = MENU_SIZE - 1;

        display_menu_show(choice);
    }

    return choice;
}

boolean game_play()
{
    map_t *map = NULL;

    map = map_load();
    if (map == NULL) return B_FALSE;

    /* unlock the basic keys */
    key_unlock('q');
    key_unlock('h');
    key_unlock('j');
    key_unlock('k');
    key_unlock('l');

    while (1) {
        display_map_show(map);

        /* if the cursor got onto a letter tile, unlock it */
        map_tile_t tile = map_get_tile(map, map -> cursor);
        if (tile.type == TILE_LETTER) {
            key_unlock(tile.value);
            display_msg_show(msg_get_keymsg(tile.value));
            display_msg_close();
        }

        if (!action_make_move(map))
            break;
    }
    return B_TRUE;
}
