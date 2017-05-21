#include "main.h"
#include "display.h"
#include "input.h"
#include "sound.h"
#include "score.h"

int main(int argc, char *argv[])
{
    int game = 0;

    /* initialize components */
    init();

    /* display the welcome message */
    display_welcome_msg();

    game = 1;
    while (game) {
        // put gameplay here
    }

    return 0;
}

void init()
{
    display_init();
    input_init();
    sound_init();
}
