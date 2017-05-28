#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "map.h"
#include "datatypes.h"

/**
 * Open and the map and initial position. Takes a map with the filename
 * initialized.
 * @param MAP* pointer to the unloaded map
 * @param POSITION* pointer to the position
 */
void map_open(MAP *map, POSITION *pos)
{
    MAP_INIT map_init;

    /* open file for reading */
    assert(map -> filepointer != NULL);
    map -> filepointer = fopen(map -> filename, "rb");
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

int map_move_valid(POSITION pos, MAP map)
{
    char requested_char;

    /* if it exceeds map size return false */
    if (pos.x > map.sizex - 1 || pos.y > map.sizey - 1) {
        return 0;
    }

    requested_char = *( map.map_data + (pos.y * map.sizex) + pos.x );

    /* define what is reachable and what is not */
    switch (requested_char) {
        case '~':
        case '+':
            return 0;
        case ' ':
        default:
            return 1;
    }
}
