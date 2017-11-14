#ifndef MAP_H_K8P4JCPW
#define MAP_H_K8P4JCPW

/**
 * Initialize the map and parameters
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean map_init();

/**
 * Load the map into map_t structure and return it
 * @return pointer to the loaded map
 */
map_t * map_load();

#endif /* end of include guard: MAP_H_K8P4JCPW */
