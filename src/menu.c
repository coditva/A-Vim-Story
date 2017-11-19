#include "datatypes.h"
#include "menu.h"
#include "interface.h"


enum menu_item menu_display()
{
    input_key_t key;
    enum menu_item choice = MENU_NEW_GAME;

    interface_display_menu(MENU_NEW_GAME);

    while (1) {
        key = interface_input_key();

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


        interface_display_menu(choice);
    }

    return choice;
}
