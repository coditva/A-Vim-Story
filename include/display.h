#ifndef DISPLAY_H
#define DISPLAY_H

#include "datatypes.h"

void                display_init();
void                display_destroy();
void                display_welcome_msg();
void                display_map(const MAP, const POSITION);
void                display_help();

#endif /* end of include guard: DISPLAY_H */
