#include <signal.h>             /* for signal() */
#include <stdlib.h>

#include "datatypes.h"
#include "game.h"
#include "interface.h"
#include "menu.h"

void signal_handler(int);

int main(int argc, char *argv[])
{
    enum menu_item choice = -1;

    /* attach handler to signals */
    signal(SIGINT , signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGSTOP, signal_handler);

    interface_init();

    while (1) {
        choice = menu_display();

        if (choice == MENU_NEW_GAME) {
            game_play();
        } else if (choice == MENU_HELP) {
            game_help();        /* display help msg */
        } else if (choice == MENU_QUIT) {
            game_exit();
            break;              /* exit the loop */
        }
    }

    /* cleanup everything */
    interface_destroy();

    return 0;
}

void signal_handler(int signal_number)
{
    interface_destroy();
    exit(1);
}
