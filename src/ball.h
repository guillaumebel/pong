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

#ifndef BALL_H_
#define BALL_H_

#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-cairo/clutter-cairo.h>

#include "config.h"

typedef struct Ball {
    ClutterActor *actor;
    float hspeed;
    float vspeed;
    float speed;
    int x;
    int y;
    int size;
} Ball;

static ClutterTimeline *explode_tl = NULL;
static ClutterEffectTemplate *explode_eff = NULL;

Ball* pong_ball_new ();

void pong_ball_set_position (Ball *p, gint x, gint y);

void pong_ball_set_size (Ball *p, gint r);

void pong_ball_explode (Ball *p);


#endif
