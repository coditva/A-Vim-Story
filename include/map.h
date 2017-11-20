/*
 * include/map.h
 * Declare the interface for handling the map in the game
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

#ifndef MAP_H_K8P4JCPW
#define MAP_H_K8P4JCPW


/**
 * Load the map into map_t structure and return it
 * @param Name of the map
 * @return pointer to the loaded map
 */
const map_t * map_open(char *);


/**
 * Unload the map
 */
void map_close();


/**
 * Check the map position and return if the position is movable
 * @param The point which is to point checked
 * @return B_TRUE is tile empty, B_FALSE otherwise
 */
boolean map_is_free(point_t);


/**
 * Return the tile on the map at the given position
 * @param The point on the map
 * @return The tile on the map
 */
map_tile_t map_get_tile(point_t);


/**
 * Grab the gem from under the cursor and update the tile to empty
 */
void map_take_gem();


/**
 * Grab the letter from under the cursor and update the tile to empty
 */
void map_take_letter();


/**
 * Update the cursor in the map to the given point
 * @param The new point for the cursor
 */
void map_set_cursor(point_t);


/**
 * Update the real_x of cursor in the map to the cursor.x
 */
void map_set_real_cursor();

#endif /* end of include guard: MAP_H_K8P4JCPW */
