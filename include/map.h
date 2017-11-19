#ifndef MAP_H_K8P4JCPW
#define MAP_H_K8P4JCPW


/**
 * Load the map into map_t structure and return it
 * @param Name of the map
 * @return pointer to the loaded map
 */
map_t * map_open(char *);


/**
 * Unload the map
 */
void map_close();


/**
 * Check the map position and return if the position is movable
 * @param The point which is to point checked
 * @return B_TRUE is tile empty, B_FALSE otherwise
 */
boolean map_is_free(point_t);


/**
 * Return the tile on the map at the given position
 * @param The point on the map
 * @return The tile on the map
 */
map_tile_t map_get_tile(point_t);


/**
 * Update the current tile to a new given tile at the given point
 * @param The point on the map
 * @param The new tile
 */
void map_set_tile(point_t, map_tile_t);


/**
 * Update the cursor in the map to the given point
 * @param The new point for the cursor
 */
void map_set_cursor(point_t);

#endif /* end of include guard: MAP_H_K8P4JCPW */
