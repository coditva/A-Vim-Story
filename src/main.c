#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "display.h"
#include "input.h"
#include "sound.h"
#include "score.h"
#include "menu.h"
#include "datatypes.h"
#include "map.h"

/* local functions */
void start_new_game();
void game_loop(MAP map, POSITION pos);


int main(int argc, char *argv[])
{
    enum MENU choice;

    /* initialize components */
    init();

    /* display the welcome message */
    display_welcome_msg();

    /* display menu and get the choice */
    choice = menu_get_choice();

    switch (choice) {
        case NEW_GAME:
            start_new_game();
        case LOAD_GAME:
        case SAVE_GAME:
        case SETTINGS:
        case HELP:
        case QUIT:
        case SIZE:
        default:
            break;
    }

    destroy();
    return 0;
}

void start_new_game()
{
    MAP map;
    POSITION pos;

    /* load default score, map, position */
    map.filename = "../data/maps/2.map";
    map.level = 1;
    map_open(&map, &pos);

    game_loop(map, pos);
}

/**
 * Run the game loop. This is where the magic happens!
 * @param MAP the map, fully initialized
 * @param POSITION the position on the map
 */
void game_loop(MAP map, POSITION pos)
{
    int game = 1;
    WINDOW *win;
    POSITION new_pos;

    /* need to get the map window use with the input */
    win = display_get_map_window();

    while (game) {

        /* display the updated map */
        display_map(map, pos);

        /* get position */
        new_pos = input_get_new_pos(win, pos);

        /* check if user requested quiting */
        if (new_pos.x == 0 && new_pos.y == 0) {
            game = 0;
        }

        /* check if move feasable and update position */
        if (map_move_valid(new_pos, map)) {
            pos.x = new_pos.x;
            pos.y = new_pos.y;
        }
    }
}

/**
 * Initialize the main process as well as the submodules
 */
void init()
{
    display_init();
    input_init();
    sound_init();
}

/**
 * Destroy the main process as well as the submodules
 */
void destroy()
{
    display_destroy();
}
