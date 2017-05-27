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

    /* load map and position */
    map.filename = "../data/maps/1.map";
    map.level = 1;
    open_map(&map, &pos);

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

    win = display_get_map_window();

    while (game) {

        /* display the updated map */
        display_map(map, pos);

        /* get input */
        switch (input_get_key(win)) {
            case 'j':
                pos.y++;
                break;
            case 'k':
                pos.y--;
                break;
            case 'h':
                pos.x--;
                break;
            case 'l':
                pos.x++;
                break;
            case 'q':
                game = 0;
                break;
            default:
                continue;
        }

        /* check if move feasable */

        /* update position */

    }
}

/**
 * Open and load map
 */
void open_map(MAP *map, POSITION *pos)
{
    MAP_INIT map_init;

    /* open file for reading */
    map -> filepointer = fopen("../data/maps/1.map", "rb");
    if (map -> filepointer == NULL) {
        fprintf(stderr, "%d - %s\n", getpid(), "Unable to open map file");
        exit(EXIT_FAILURE);
    }

    /* load initial variables */
    fread(&map_init, sizeof(MAP_INIT), 1, map -> filepointer); 

    map -> sizex = map_init.sizex;
    map -> sizey = map_init.sizey;
    pos -> x = map_init.startx;
    pos -> y = map_init.starty;

    /* load the map from start */
    map -> map_data = (char *) malloc((map -> sizex + 2) * map -> sizey);
    fseek(map -> filepointer, sizeof(MAP_INIT), SEEK_SET);
    fgets(map -> map_data, (map -> sizex + 2) * map -> sizey,
            map -> filepointer);

    /* close the file */
    fclose(map -> filepointer);
    map -> filepointer = NULL;
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
