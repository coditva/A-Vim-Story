/*
 * src/map.c
 * Define the module for handling the map in the game
 *
 * Copyright (C) 2017 Utkarsh Mahshwari <utkarshme96@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>             /* for free(), NULL */
#include <string.h>             /* for strcpy() */
#include <dlfcn.h>              /* for dlopen(), etc */

#include "datatypes.h"
#include "map.h"


map_t *map = NULL;              /* store the map here globally */


/* convert the point to a linear index and return */
int convert_point_to_linear(point_t);

/* parse the mapfile and return the map object */
map_t * parse_mapfile(mapfile_data_t *);


const map_t * map_open(char *map_name)
{
    mapfile_data_t *mapfile_data;
    void *handle;
    /* LIB_DIR from the generated config.h header */
    char map_path[150] = LIB_DIR;

    /* open the map */
    strcat(map_path, "/maps/map");
    strcat(map_path, map_name);
    if (!(handle = dlopen(map_path, RTLD_NOW)))
        return NULL;

    /* get the function */
    if (!(mapfile_data = (mapfile_data_t *) dlsym(handle, "map")))
        return NULL;

    /* get the parsed map */
    map = parse_mapfile(mapfile_data);

    dlclose(handle);
    return map;
}

void map_close()
{
    free(map -> data);
    free(map -> story);
    free(map);
}

boolean map_is_free(point_t point)
{
    int pos = convert_point_to_linear(point);

    if (map -> data[pos].type == TILE_GRASS
            || map -> data[pos].type == TILE_DOOR
            || map -> data[pos].type == TILE_GEM
            || map -> data[pos].type == TILE_TEXT
            || map -> data[pos].type == TILE_LETTER) {
        return B_TRUE;
    }
    return B_FALSE;
}

map_tile_t map_get_tile(point_t point)
{
    return map -> data[convert_point_to_linear(point)];
}

void map_set_tile(point_t point, map_tile_t tile)
{
    map -> data[convert_point_to_linear(point)] = tile;
}

int convert_point_to_linear(point_t point)
{
    return map -> size.x * point.y + point.x;
}

map_t * parse_mapfile(mapfile_data_t *buffer)
{
    int pos = 0;

    map = (map_t *) malloc(sizeof(map_t));

    map -> size.y = buffer -> size.y;
    map -> size.x = buffer -> size.x;
    map -> cursor.y = buffer -> cursor.y;
    map -> cursor.x = buffer -> cursor.x;
    map -> real_x = buffer -> cursor.x;
    map -> letters_left = 0;

    map -> data = (map_tile_t *) malloc(sizeof(map_tile_t)
            * map -> size.x * map -> size.y);

    for (int i = 0; i < map -> size.y; ++i) {
        for (int j = 0; j < map -> size.x; ++j) {
            map -> data[pos].value = ' ';
            switch (buffer -> data[i][j]) {
                case '+':
                    map -> data[pos].type = TILE_BORDER;
                    break;
                case '-':
                    map -> data[pos].type = TILE_TEXT;
                    map -> data[pos].value = ' ';
                    break;
                case ' ':
                    map -> data[pos].type = TILE_GRASS;
                    break;
                default:
                    map -> data[pos].type = TILE_TEXT;
                    map -> data[pos].value = buffer -> data[i][j];
            }
            pos++;
        }
    }

    /* add door */
    pos = convert_point_to_linear(buffer -> exit);
    map -> data[pos].type = TILE_DOOR;

    /* add gems */
    map -> gems_left = buffer -> gems.count;
    for (int i = 0; i < buffer -> gems.count; ++i) {
        pos = convert_point_to_linear(buffer -> gems.data[i]);
        map -> data[pos].type = TILE_GEM;
    }

    /* add story */
    map -> story = (char *) malloc(strlen(buffer -> story) + 1);
    strcpy(map -> story, buffer -> story);

    /* add letters */
    map -> letters_left = buffer -> letters.count;
    for (int i = 0; i < buffer -> letters.count; ++i) {
        pos = convert_point_to_linear(buffer -> letters.data[i].point);
        map -> data[pos].type = TILE_LETTER;
        map -> data[pos].value = buffer -> letters.data[i].value;
    }

    return map;
}

void map_take_gem()
{
    map_tile_t tile;
    tile.type = TILE_GRASS;
    tile.value = ' ';

    map_set_tile(map -> cursor, tile);
    map -> gems_left--;
}

void map_take_letter()
{
    map_tile_t tile;
    tile.type = TILE_GRASS;
    tile.value = ' ';

    map_set_tile(map -> cursor, tile);
    map -> letters_left--;
}

void map_set_cursor(point_t point)
{
    map -> cursor.y = point.y;
    map -> cursor.x = point.x;
}

void map_set_real_cursor()
{
    map -> real_x = map -> cursor.x;
}

point_t * map_search_tile(map_tile_t searchtile, int step)
{
    map_tile_t tile;
    point_t *point = (point_t *) malloc(sizeof(point_t));

    point -> x = map -> cursor.x;
    point -> y = map -> cursor.y;

    while (point -> x < map -> size.x || point -> y < map -> size.y) {
        tile = map_get_tile(*point);
        if (tile.type == searchtile.type && tile.value == searchtile.value) {
            return point;
        }
        point -> x += step;
        if (point -> x > map -> size.x) {
            point -> x = 0;
            point -> y += (step > 0) ? 1 : -1;
        }
    }
    return NULL;
}
