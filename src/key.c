#include "datatypes.h"
#include "key.h"


/* store which all keys have been unlocked */
boolean unlocked[KEY_MAX_SIZE];


boolean key_unlocked(input_key_t key)
{
    return unlocked[key];
}

void key_lock(input_key_t key)
{
    unlocked[key] = B_FALSE;
}

void key_unlock(input_key_t key)
{
    unlocked[key] = B_TRUE;
}

void key_lock_all()
{
    for (int i = 0; i < KEY_MAX_SIZE; ++i) unlocked[i] = B_FALSE;
}

void key_unlock_all()
{
    for (int i = 0; i < KEY_MAX_SIZE; ++i) unlocked[i] = B_TRUE;
}
