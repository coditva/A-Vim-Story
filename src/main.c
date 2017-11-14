#include <unistd.h>             /* for sleep() */
#include <ncurses.h>            /* for input key enum */


#include "config.h"
#include "datatypes.h"
#include "map.h"
#include "display.h"
#include "input.h"


/* Displays menu on top of everything and gets the user choice */
enum menu_item get_menu_choice();


int main(int argc, char *argv[])
{
    enum menu_item choice = -1;

    display_init();
    input_init();

    choice = get_menu_choice();

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
