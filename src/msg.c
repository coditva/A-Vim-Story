#include <stdlib.h>             /* for malloc() */
#include <string.h>             /* for strlen(), strcpy() */

#include "datatypes.h"
#include "msg.h"

#define MAX_MSG_SIZE 100
#define START 32                /* the first key character */
char message[KEY_MAX_SIZE - START][MAX_MSG_SIZE] = {
    /* start from START ie 'space' */
    "You unlocked 'space'",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "You unlocked 0.",
    "You unlocked 1.",
    "You unlocked 2.",
    "You unlocked 3.",
    "You unlocked 4.",
    "You unlocked 5.",
    "You unlocked 6.",
    "You unlocked 7.",
    "You unlocked 8.",
    "You unlocked 9.",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked  .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked A .",
    "You unlocked Z .",
    "You unlocked   .",
    "You unlocked   .",
    "You unlocked   .",
    "You unlocked   .",
    "You unlocked   .",
    "You unlocked   .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked h .",
    "You unlocked a .",
    "You unlocked j .",
    "You unlocked k .",
    "You unlocked l .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked a .",
    "You unlocked z .",
    "You unlocked   .",
    "You unlocked   .",
    "You unlocked   .",
    "You unlocked   .",
};


boolean msg_init()
{
    return B_TRUE;
}

char * msg_get_keymsg(input_key_t key)
{
    return message[key - START];
}

boolean msg_destroy()
{
    /* clear all the messages */
    return B_TRUE;
}
