#include "datatypes.h"
#include "map.h"
#include "display.h"
#include "input.h"
#include "msg.h"
#include "game.h"
#include "menu.h"


int main(int argc, char *argv[])
{
    enum menu_item choice = -1;
    game_t game;

    /* initialize everything */
    display_init();
    input_init();
    msg_init();

    while (1) {
        choice = menu_display();

        if (choice == MENU_NEW_GAME) {
            if (!(game.map = map_load("1"))) return 1;
            game_play(game);
            map_free(game.map);
        } else if (choice == MENU_HELP) {
            /* display help msg */
        } else if (choice == MENU_QUIT) {
            break;              /* exit the controller loop */
        }
    }

    /* cleanup everything */
    msg_destroy();
    display_destroy();

    return 0;
}
