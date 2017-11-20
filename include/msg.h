/*
 * include/msg.h
 * Declare the interface for getting the messages for keys
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

#ifndef MSG_H_TQLNM5HF
#define MSG_H_TQLNM5HF


/**
 * Get the message for a given key
 * @param The key for which to get the message
 * @return The message for the key
 */
char * msg_get_keymsg(input_key_t);

#endif /* end of include guard: MSG_H_TQLNM5HF */
