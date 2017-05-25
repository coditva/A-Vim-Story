#ifndef DATATYPES_H
#define DATATYPES_H

/**
 * Enumeration for menu items
 */
enum MENU
{
    NEW_GAME,
    LOAD_GAME,
    SAVE_GAME,
    SETTINGS,
    HELP,
    QUIT,
    SIZE
};

/**
 * Datatype for storing map details
 */
typedef struct MAP_STRUCT
{
    int level;
    char *filename;
    FILE *filepointer;
    int sizex;
    int sizey;
} MAP;

/**
 * Datatype for initial map variables
 */
typedef struct MAP_INIT_STRUCT
{
    int sizex;
    int sizey;
    int startx;
    int starty;
} MAP_INIT;

/**
 * Position of the cursor
 */
typedef struct POSITION_STRUCT
{
    int x;
    int y;
} POSITION;

#endif /* end of include guard: DATATYPES_H */
