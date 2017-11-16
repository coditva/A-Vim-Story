#ifndef MAP_H_K8P4JCPW
#define MAP_H_K8P4JCPW

/**
 * Initialize the map and parameters
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean map_init();

/**
 * Load the map into map_t structure and return it
 * @param Name of the map
 * @return pointer to the loaded map
 */
map_t * map_load(char *);

/**
 * Unload the map
 * @param Pointer to the map
 */
void map_free(map_t *);

/**
 * Check the map position and return if the position is movable
 * @return B_TRUE is tile empty, B_FALSE otherwise
 */
boolean map_is_free(map_t *, point_t);

/**
 * Return the tile on the map at the given position
 * @param The pointer to the map
 * @param The point on the map
 * @return The tile on the map
 */
map_tile_t map_get_tile(map_t *, point_t);

/**
 * Update the current tile to a new given tile at the given point
 * @param The pointer to the map
 * @param The point on the map
 * @param The new tile
 */
void map_set_tile(map_t *, point_t, map_tile_t);

#endif /* end of include guard: MAP_H_K8P4JCPW */
