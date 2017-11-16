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
