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
#ifndef CONFIG_H_
#define CONFIG_H_

#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gdk/gdkkeysyms.h>
#include <gconf/gconf-client.h>

#include "color.h"

#define REBOND 7

#define PADDLE_TINY_W 8
#define PADDLE_TINY_H 50
#define PADDLE_NORMAL_W 11  
#define PADDLE_NORMAL_H 70
#define PADDLE_BIG_W 14
#define PADDLE_BIG_H 90

#define PADDLE_SIZE 2

#define BALL_TINY 8
#define BALL_NORMAL 12
#define BALL_BIG 15

#define SCREEN_W 480
#define SCREEN_H 380

#define WIN_SCORE 10
#define DIFFICULTY 2


typedef struct Config {
    int screen_w;
    int screen_h;
    int difficulty; //difficulty easy, medium. hard
    PongColor color_player1;
    PongColor color_player2;
    PongColor16 background_color;
    int win_score;
    gboolean two_player;
    int paddle_size; //tiny, normal, big 
    int ball_size; //tiny, normal, big
} Config;

static const char* pong_key_name[] = {
    "width",
    "height",
    "difficulty",
    "player1_color",
    "player2_color",
    "background_color",
    "paddle_size",
    "win_score",
    NULL
};

GConfClient *client = NULL;

void pong_config_init ();
Config* pong_config_get_stored ();
void pong_config_reset_default ();
void pong_config_set_string (gchar *key, gchar *value);
void pong_config_set_int (gchar *key, gint value);
void pong_config_set_float (gchar *key, gdouble value);
void pong_config_set_boolean (gchar *key, gboolean value);
gchar* pong_config_get_string (gchar *key);
gboolean pong_config_get_bool (gchar *key);
gint pong_config_get_int (gchar *key);
gdouble pong_config_get_float (gchar *key);
PongColor pong_config_get_color (gchar *key);
PongColor16 pong_config_get_color16 (gchar *key);

#endif
