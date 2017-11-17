#include <stdlib.h>             /* for free(), NULL */
#include <string.h>             /* for strcpy() */
#include <dlfcn.h>              /* for dlopen(), etc */
#include <assert.h>

#include "datatypes.h"
#include "map.h"

/* Define the type for map pointer */
typedef void * (*map_func_t)(void);


/* Convert the point to a linear index and return */
int convert_point_to_linear(map_t *, point_t);
map_t * parse_mapfile(mapfile_data_t *);


boolean map_init()
{
    return B_TRUE;
}

map_t * map_load(char *map_name)
{
    map_t *map = NULL;
    char map_path[100] = "maps/map";
    mapfile_data_t *mapfile_data;
    void *handle;

    /* open the map */
    strcat(map_path, map_name);
    handle = dlopen(map_path, RTLD_NOW);
    if (!handle) return NULL;

    /* get the function */
    mapfile_data = (mapfile_data_t *) dlsym(handle, "map");
    assert(mapfile_data);
    if (!mapfile_data) return NULL;

    /* get the parsed map */
    map = parse_mapfile(mapfile_data);

    dlclose(handle);
    return map;
}

void map_free(map_t *map)
{
    free(map -> data);
    free(map);
}

boolean map_is_free(map_t *map, point_t point)
{
    int pos = convert_point_to_linear(map, point);

    if (map -> data[pos].type == TILE_GRASS
            || map -> data[pos].type == TILE_DOOR
            || map -> data[pos].type == TILE_GEM
            || map -> data[pos].type == TILE_LETTER) {
        return B_TRUE;
    }
    return B_FALSE;
}

map_tile_t map_get_tile(map_t *map, point_t point)
{
    return map -> data[convert_point_to_linear(map, point)];
}

void map_set_tile(map_t *map, point_t point, map_tile_t tile)
{
    map -> data[convert_point_to_linear(map, point)] = tile;
}

int convert_point_to_linear(map_t *map, point_t point)
{
    return map -> size.x * point.y + point.x;
}

map_t * parse_mapfile(mapfile_data_t *buffer)
{
    map_t *map = NULL;
    int pos = 0;

    map = (map_t *) malloc(sizeof(map_t));

    map -> size.y = buffer -> size.y;
    map -> size.x = buffer -> size.x;
    map -> cursor.y = buffer -> cursor.y;
    map -> cursor.x = buffer -> cursor.x;
    map -> real_x = buffer -> cursor.x;

    map -> data = (map_tile_t *) malloc(sizeof(map_tile_t)
            * map -> size.x * map -> size.y);

    for (int i = 0; i < map -> size.y; ++i) {
        for (int j = 0; j < map -> size.x; ++j) {
            map -> data[pos].value = ' ';
            switch (buffer -> data[i][j]) {
                case '+':
                    map -> data[pos].type = TILE_WATER;
                    break;
                case '-':
                    map -> data[pos].type = TILE_LETTER;
                    map -> data[pos].value = ' ';
                    break;
                case ' ':
                    map -> data[pos].type = TILE_GRASS;
                    break;
                default:
                    map -> data[pos].type = TILE_LETTER;
                    map -> data[pos].value = buffer -> data[i][j];
            }
            pos++;
        }
    }

    /* add door */
    pos = convert_point_to_linear(map, buffer -> exit);
    map -> data[pos].type = TILE_DOOR;

    /* add gems */
    map -> gems_left = buffer -> gems.count;
    for (int i = 0; i < buffer -> gems.count; ++i) {
        pos = convert_point_to_linear(map, buffer -> gems.data[i]);
        map -> data[pos].type = TILE_GEM;
    }

    return map;
}
