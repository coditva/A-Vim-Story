#ifndef DATATYPES_H_PH0MEKHP
#define DATATYPES_H_PH0MEKHP


/**
 * A type to store boolean values:
 * B_TRUE and B_FALSE
 */
typedef enum { B_FALSE, B_TRUE } boolean;


/**
 * Enum to store the number of items in the menu
 */
enum menu_item {
    MENU_NEW_GAME,
    MENU_HELP,
    MENU_QUIT,
    MENU_SIZE
};


/**
 * Define the input key type
 */
typedef int input_key_t;


/**
 * A data structure to store the 2D point pair
 */
typedef struct {
    int x;
    int y;
} point_t;


/**
 * Define the types of tiles in the map
 */
typedef enum {
    TILE_WATER,
    TILE_BORDER,
    TILE_BRICK,
    TILE_GRASS,
} map_tile_t;


/**
 * A data structure to store the map
 */
typedef struct {
    point_t size;
    point_t cursor;
    map_tile_t *data;
} map_t;


#endif /* end of include guard: DATATYPES_H_PH0MEKHP */
