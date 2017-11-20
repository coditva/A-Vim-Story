/*
 * include/key.h
 * Declare the interface for locking/unlocking keys in the game
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

#ifndef KEY_H_PTVHEK7H
#define KEY_H_PTVHEK7H


/**
 * Check if a key is unlocked in the game
 * @param The key to check
 * @return B_TRUE if unlocked, B_FALSE otherwise
 */
boolean key_unlocked(const input_key_t);


/**
 * Unlock all the keys
 */
void key_unlock_all();


/**
 * Lock all the keys
 */
void key_lock_all();


/**
 * Unlock the given key
 * @param The key to unlock
 */
void key_unlock(const input_key_t);


/**
 * Lock the given key
 * @param The key to lock
 */
void key_lock(const input_key_t);


#endif /* end of include guard: KEY_H_PTVHEK7H */
