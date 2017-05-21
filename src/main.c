#include "main.h"
#include "display.h"
#include "input.h"
#include "sound.h"
#include "score.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    int game = 0;

    /* initialize components */
    init();

    /* display the welcome message */
    display_welcome_msg();
    menu_get_choice();

    game = 1;
    while (game) {
        // put gameplay here
        game = 0;
    }

    destroy();
    return 0;
}

/**
 * Initialize the main process as well as the submodules
 */
void init()
{
    display_init();
    input_init();
    sound_init();
}

/**
 * Destroy the main process as well as the submodules
 */
void destroy()
{
    display_destroy();
}
