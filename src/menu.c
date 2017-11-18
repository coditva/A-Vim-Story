#include "datatypes.h"
#include "menu.h"
#include "display.h"
#include "input.h"


enum menu_item menu_display()
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
                if (choice == MENU_SIZE) choice = 0;
                break;
            case 'k':
                if (choice == 0) choice = MENU_SIZE;
                choice--;
                break;
            default:
                continue;
        }


        display_menu_show(choice);
    }

    return choice;
}
