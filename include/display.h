#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "datatypes.h"

void                display_init();
void                display_destroy();
void                display_welcome_msg();
void                display_map(MAP, POSITION);
void                display_help();

WINDOW *            display_get_map_window();
WINDOW *            display_get_main_window();
WINDOW *            display_get_status_window();
void                display_set_main_window();
void                display_set_map_window();
void                display_set_status_window();

#endif /* end of include guard: DISPLAY_H */
