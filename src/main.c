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

    display_init();
    input_init();
    msg_init();

    while (1) {
        choice = menu_display();

        if (choice == MENU_NEW_GAME) {
            if (!(game.map = map_load())) return 1;
            game_play(game);
        } else if (choice == MENU_HELP) {
            /* display help msg */
        } else if (choice == MENU_QUIT) {
            break;              /* exit the controller loop */
        }
    }

    display_destroy();
    return 0;
}
