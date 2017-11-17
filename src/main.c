#include "datatypes.h"
#include "game.h"
#include "display.h"
#include "input.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    enum menu_item choice = -1;

    display_init();
    input_init();

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
    display_destroy();

    return 0;
}
