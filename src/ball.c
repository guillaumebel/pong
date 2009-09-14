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
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>

#include "ball.h"
#include "pong.h"

extern GdkPixbuf* pong_pixbuf[];

PongBall *
pong_ball_new (void) 
{
  PongBall *ball = g_new (PongBall,1);

  ball->speed = 3;
  ball->x = SCREEN_W / 2;
  ball->y = SCREEN_H / 2;
  ball->size = BALL_NORMAL;

  srand (time (NULL));
  float dir = ((float) (rand() % 9100 - 4600) / 100) * (M_PI / 180);
  ball->hspeed = ball->speed * cos (dir);
  ball->vspeed = ball->speed * sin (dir);
  
  ball->actor = gtk_clutter_texture_new_from_pixbuf (pong_pixbuf[0]);

  return ball;
}

void
pong_ball_set_position (PongBall *ball, gfloat x, gfloat y)
{
  clutter_actor_set_position (CLUTTER_ACTOR (ball->actor), x, y);
}

void
pong_ball_set_size (PongBall *ball, gint r)
{
  ball->size = r;
  clutter_actor_set_size (CLUTTER_ACTOR (ball->actor), r, r);
}

