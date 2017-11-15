#include <ncurses.h>

#include "datatypes.h"
#include "input.h"

boolean input_init()
{
    noecho();
    return B_TRUE;
}

input_key_t input_get_key()
{
    return getch();
}
