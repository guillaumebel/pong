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

#include "paddle.h"

Paddle* pong_paddle_new ()
{
    cairo_t *cr;
    cairo_pattern_t *pattern;
    Paddle *pad = g_new (Paddle,1);

    pad->size = PADDLE_H;
    pad->width = PADDLE_W;
    pad->speed = 3;

    pad->actor = clutter_cairo_new (PADDLE_W * 2, PADDLE_W * 2);
    cr = clutter_cairo_create (CLUTTER_CAIRO (pad->actor));

    cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
    cairo_paint (cr);
    cairo_set_operator (cr, CAIRO_OPERATOR_ADD);

    cairo_rectangle (cr, 0, 0, PADDLE_W, PADDLE_H);
    
    pattern = cairo_pattern_create_linear (0, PADDLE_H / 2, 
                                                PADDLE_W, PADDLE_H / 2);

    cairo_pattern_add_color_stop_rgba (pattern, 0.40,  0.09, 0.18, 0.33, 0.75);
    cairo_pattern_add_color_stop_rgba (pattern, 0.75,  0.25, 0.5, .85, 0.75);

    cairo_set_source (cr, pattern);
    cairo_fill (cr);

    cairo_pattern_destroy (pattern);
    cairo_destroy (cr);
  
    return pad;
}

void pong_paddle_set_color (Paddle *p, PongColor start, PongColor stop)
{
    cairo_t *cr;
    cairo_pattern_t *pattern;

    cr = clutter_cairo_create (CLUTTER_CAIRO (p->actor));

    cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
    cairo_paint (cr);
    cairo_set_operator (cr, CAIRO_OPERATOR_ADD);

    cairo_rectangle (cr, 0, 0, PADDLE_W, PADDLE_H);
    
    pattern = cairo_pattern_create_linear (0, PADDLE_H / 2, 
                                                PADDLE_W, PADDLE_H / 2);

    cairo_pattern_add_color_stop_rgba (pattern, 0.40,  start.red, 
                                                       start.green, 
                                                       start.blue, 
                                                       start.alpha);

    cairo_pattern_add_color_stop_rgba (pattern, 0.75,  stop.red, 
                                                       stop.green, 
                                                       stop.blue, 
                                                       stop.alpha);

    cairo_set_source (cr, pattern);
    cairo_fill (cr);

    cairo_pattern_destroy (pattern);
    cairo_destroy (cr);
}

void pong_paddle_set_position (Paddle *p, gint x, gint y)
{
    clutter_actor_set_position (CLUTTER_ACTOR (p->actor), x, y);
}

void pong_paddle_set_size (Paddle *p, gint w, int h)
{
    p->width = w;
    p->size = h;
    clutter_actor_set_size (CLUTTER_ACTOR (p->actor), w, h);
}
