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


boolean map_init()
{
    return B_TRUE;
}

map_t * map_load(char *map_name)
{
    map_t *map = NULL;
    char map_path[100] = "maps/map";
    map_func_t get_map;
    void *handle;

    /* open the map */
    strcat(map_path, map_name);
    handle = dlopen(map_path, RTLD_NOW);
    assert(handle);
    if (!handle) return NULL;

    /* get the function */
    get_map = (map_func_t) dlsym(handle, "get_map");
    assert(get_map);
    if (!get_map) return NULL;

    /* run the function to get the map */
    map = (*get_map)();

    /* destroy the function, map */
    get_map = NULL;
    dlclose(handle);

    return map;
}

void map_free(map_t *map)
{
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
