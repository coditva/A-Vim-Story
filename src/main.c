#include <unistd.h>             /* for sleep() */
#include <ncurses.h>            /* for input key enum */


#include "config.h"
#include "datatypes.h"
#include "map.h"
#include "display.h"
#include "input.h"


/* Displays menu on top of everything and gets the user choice */
enum menu_item get_menu_choice();

/* Play the game */
boolean game_play();


int main(int argc, char *argv[])
{
    enum menu_item choice = -1;

    display_init();
    input_init();

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
    input_key_t key;
    int loop = 1;
    point_t point;

    map = map_load();
    if (map == NULL) return B_FALSE;

    while (loop) {
        display_map_show(map);
        key = input_get_key();
        switch (key) {
            case 'j':
                point.x = map -> cursor.x;
                point.y = map -> cursor.y + 1;
                break;
            case 'k':
                point.x = map -> cursor.x;
                point.y = map -> cursor.y - 1;
                break;
            case 'l':
                point.x = map -> cursor.x + 1;
                point.y = map -> cursor.y;
                break;
            case 'h':
                point.x = map -> cursor.x - 1;
                point.y = map -> cursor.y;
                break;
            case 'q':
                loop = 0;
                break;
        }

        if (map_is_free(map, point)) {
            map -> cursor.x = point.x;
            map -> cursor.y = point.y;
        }
    }
    return B_TRUE;
}
