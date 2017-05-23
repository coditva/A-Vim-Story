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

int main(int argc, char *argv[])
{
    int game = 0;
    MAP map;
    POSITION pos;

    /* initialize components */
    init();

    /* display the welcome message */
    display_welcome_msg();
    menu_get_choice();

    game = 1;

    /* load map and position */
    map.filename = "../data/maps/1.map";
    map.level = 1;
    open_map(&map, &pos);

    while (game) {
        /* display the updated map */
        display_map(map, pos);

        /* get input */

        /* check if move feasable */

        /* update position */

        game = 0; // remove this after loop is complete
    }

    destroy();
    return 0;
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
