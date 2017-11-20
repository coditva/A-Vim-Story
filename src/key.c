/*
 * src/key.c
 * Define the module for locking/unlocking keys in the game
 *
 * Copyright (C) 2017 Utkarsh Mahshwari <utkarshme96@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
