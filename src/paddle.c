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
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>

#include "paddle.h"
#include "pong.h"

extern GdkPixbuf *pong_pixbuf[];

PongPaddle*
pong_paddle_new (gint number)
{
  PongPaddle *pad = g_new (PongPaddle,1);

  pad->size = PADDLE_NORMAL_H;
  pad->width = PADDLE_NORMAL_W;
  pad->speed = 3;
  pad->number = number;

  pad->actor = gtk_clutter_texture_new_from_pixbuf (pong_pixbuf[number]);
  clutter_actor_set_size (pad->actor, 
                          PADDLE_NORMAL_W * 2, 
                          PADDLE_NORMAL_H * 2);
  
  return pad;
}

void
pong_paddle_set_position (PongPaddle *p, gfloat x, gfloat y)
{
  clutter_actor_set_position (CLUTTER_ACTOR (p->actor), x, y);
}

void
pong_paddle_set_size (PongPaddle *p, gint w, gint h)
{
  p->width = w;
  p->size = h;
  clutter_actor_set_size (CLUTTER_ACTOR (p->actor), w, h);
}

