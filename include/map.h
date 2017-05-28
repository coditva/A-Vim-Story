#ifndef MAP_H
#define MAP_H

#include "datatypes.h"

void                map_open(MAP *, POSITION *);
POSITION            map_get_pos(POSITION, int);
int                 map_move_valid(POSITION, MAP);

#endif /* end of include guard: MAP_H */
