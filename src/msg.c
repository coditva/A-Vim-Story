#include <stdlib.h>             /* for malloc() */
#include <string.h>             /* for strlen(), strcpy() */

#include "datatypes.h"
#include "msg.h"

#define MAX_MSG_SIZE 100
char message[KEY_MAX_SIZE][MAX_MSG_SIZE];


boolean msg_init()
{
    strcpy(message['h'], "You unlocked 'h'. This makes you go left.");
    strcpy(message['j'], "You unlocked 'j'. This makes you go down.");
    strcpy(message['k'], "You unlocked 'k'. This makes you go up.");
    strcpy(message['l'], "You unlocked 'l'. This makes you go right.");
    return B_TRUE;
}

char * msg_get_keymsg(input_key_t key)
{
    return message[key];
}

boolean msg_destroy()
{
    /* clear all the messages */
    return B_TRUE;
}
