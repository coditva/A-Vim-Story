/*
 * include/action.h
 * Declare the interface to handle user input
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

#ifndef ACTION_H_D9AS6ZWN
#define ACTION_H_D9AS6ZWN

/**
 * Take a key as input and update the map checking if the move is valid or not
 * @param The map to update
 * @return The command entered by the user
 */
command_t action_make_move(const map_t *map);

#endif /* end of include guard: ACTION_H_D9AS6ZWN */
