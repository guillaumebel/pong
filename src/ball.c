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

#include "ball.h"

static void explode_end (ClutterTimeline *timeline, gpointer data);

Ball* pong_ball_new ()
{
    cairo_t *cr;
    cairo_pattern_t *pattern;
    Ball *b = g_new (Ball,1);

    b->speed = 3;
    b->x = SCREEN_W / 2;
    b->y = SCREEN_H / 2;
    b->size = BALL_NORMAL;

    srand(time(NULL));
    float dir = ((float)(rand() % 9100 - 4600) / 100) * (M_PI/180);
    b->hspeed = b->speed * cos(dir);
    b->vspeed = b->speed * sin(dir);

    b->actor = clutter_cairo_new (BALL_NORMAL * 2, BALL_NORMAL * 2);
    cr = clutter_cairo_create (CLUTTER_CAIRO (b->actor));

    cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
    cairo_paint (cr);
    cairo_set_operator (cr, CAIRO_OPERATOR_ADD);

    cairo_arc (cr, BALL_NORMAL, BALL_NORMAL, BALL_NORMAL, 0.0, 2 * M_PI);

    pattern = cairo_pattern_create_radial (BALL_NORMAL, BALL_NORMAL, 0,
                                                BALL_NORMAL, BALL_NORMAL, BALL_NORMAL);
    cairo_pattern_add_color_stop_rgba (pattern, 0, 0.88, 0.95, 0.99, 0.1);
    cairo_pattern_add_color_stop_rgba (pattern, 0.6, 0.88, 0.95, 0.99, 0.1);
    cairo_pattern_add_color_stop_rgba (pattern, 0.8, 0.67, 0.83, 0.91, 0.2);
    cairo_pattern_add_color_stop_rgba (pattern, 0.9, 0.5, 0.67, 0.88, 0.7);
    cairo_pattern_add_color_stop_rgba (pattern, 1.0, 0.3, 0.43, 0.69, 0.8);

    cairo_set_source (cr, pattern);
    cairo_fill_preserve (cr);

    cairo_pattern_destroy (pattern);

    pattern = cairo_pattern_create_linear (0, 0, BALL_NORMAL * 2, BALL_NORMAL * 2);
    cairo_pattern_add_color_stop_rgba (pattern, 0.0, 1.0, 1.0, 1.0, 0.0);
    cairo_pattern_add_color_stop_rgba (pattern, 0.15, 1.0, 1.0, 1.0, 0.95);
    cairo_pattern_add_color_stop_rgba (pattern, 0.3, 1.0, 1.0, 1.0, 0.0);
    cairo_pattern_add_color_stop_rgba (pattern, 0.7, 1.0, 1.0, 1.0, 0.0);
    cairo_pattern_add_color_stop_rgba (pattern, 0.85, 1.0, 1.0, 1.0, 0.95);
    cairo_pattern_add_color_stop_rgba (pattern, 1.0, 1.0, 1.0, 1.0, 1.0);

    cairo_set_source (cr, pattern);
    cairo_fill_preserve (cr);

    cairo_set_source_rgba(cr, 1, 1, 1, 0.6);
    cairo_set_source (cr, pattern);
    cairo_fill (cr);

    cairo_pattern_destroy (pattern);
    cairo_destroy (cr);
  
    return b;
}

void pong_ball_set_position (Ball *b, gint x, gint y)
{
    clutter_actor_set_position (CLUTTER_ACTOR (b->actor), x, y);
}

void pong_ball_set_size (Ball *b, gint r)
{
    b->size = r;
    clutter_actor_set_size (CLUTTER_ACTOR (b->actor), r, r);
}

void 
pong_ball_explode (Ball *p)
{
    
    if (!explode_tl)
        explode_tl = clutter_timeline_new_for_duration (360);
    if (!explode_eff)
        explode_eff = clutter_effect_template_new (explode_tl, CLUTTER_ALPHA_SINE_INC);
    
    clutter_effect_fade (explode_eff, p->actor, 0, NULL, NULL);
    clutter_effect_move (explode_eff, p->actor, 
                            p->x + g_random_int_range (-60 - p->size / 4, 60),
                            p->y + g_random_int_range (-60 - p->size / 4, 60),
                            NULL, NULL);
    clutter_effect_scale (explode_eff, p->actor, 1.5, 1.5, NULL, NULL);

    
    clutter_timeline_start (explode_tl);

    g_signal_connect (explode_tl, "completed",
                        G_CALLBACK (explode_end), p);
}

static void
explode_end (ClutterTimeline *tl, gpointer data)
{
    Ball *tmp = (Ball *)data;
    clutter_actor_set_opacity (CLUTTER_ACTOR (tmp->actor), 0xff);
    pong_ball_set_size(tmp, tmp->size);
    
    //g_free (tmp);
    //g_free (tl);
}
