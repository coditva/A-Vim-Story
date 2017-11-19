#include "datatypes.h"
#include "game.h"
#include "interface.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    enum menu_item choice = -1;

    interface_init();

    while (1) {
        choice = menu_display();

        if (choice == MENU_NEW_GAME) {
            game_play();
        } else if (choice == MENU_HELP) {
            /* display help msg */
        } else if (choice == MENU_QUIT) {
            break;              /* exit the loop */
        }
    }

    /* cleanup everything */
    interface_destroy();

    return 0;
}
