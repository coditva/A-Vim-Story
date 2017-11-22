/*
 * include/command.c
 * Declare the interface for taking and executing commands
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

#ifndef COMMAND_H_0TNF49V3
#define COMMAND_H_0TNF49V3


/**
 * Ask user for input and build the command
 * @return The pointer to the command
 */
command_t * command_get();


/**
 * Execute the command on the given map
 * @param The pointer to the map
 * @patam The pointer to the command
 */
void command_exec(const map_t *, const command_t *);


#endif /* end of include guard: COMMAND_H_0TNF49V3 */
