/*
 * Copyright(C) 2009 Guillaume Béland <guillaume.beland@gmail.com>
 *
 * Author: Guillaume Béland (guillaumebel) <guillaume.beland@gmail.com>
 *
 * This file is part of Pong!.
 *
 * Pong! is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Pong! is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef PADDLE_H_
#define PADDLE_H_

#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-cairo/clutter-cairo.h>

#include "color.h"

#define PADDLE_W 8     // paddle width
#define PADDLE_H 50    //paddle height

typedef struct Paddle {
    ClutterActor *actor;
    int size;
    int width;
    int speed;
} Paddle;

Paddle* pong_paddle_new ();

void pong_paddle_set_color (Paddle *p, PongColor start, PongColor stop);

void pong_paddle_set_position (Paddle *p, gint x, gint y);

void pong_paddle_set_size (Paddle *p, gint w, gint h);

#endif
