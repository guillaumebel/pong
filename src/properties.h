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
#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gdk/gdkkeysyms.h>
#include <gconf/gconf-client.h>

#define REBOND 7

#define PADDLE_TINY_W 8
#define PADDLE_TINY_H 50
#define PADDLE_NORMAL_W 10  
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
#define TWO_PLAYER 0

#define GCONF_DIR "/apps/pong"
#define WIDTH_KEY GCONF_DIR "/width"
#define HEIGHT_KEY GCONF_DIR "/height"
#define DIFFICULTY_KEY GCONF_DIR "/difficulty"
#define WINSCORE_KEY GCONF_DIR "/win_score"
#define PADDLESIZE_KEY GCONF_DIR "/paddle_size"
#define TWOPLAYER_KEY GCONF_DIR "/two_player"
#define BALLSIZE_KEY GCONF_DIR "/ball_size"

typedef struct PongProperties {
	int screen_w;
	int screen_h;
	int difficulty; //difficulty easy, medium. hard
	int win_score;
	gboolean two_player;
	int paddle_size; //tiny, normal, big 
	int ball_size; //tiny, normal, big
} PongProperties;

static const char* pong_key_name[] = {
	"width",
	"height",
	"difficulty",
	"paddle_size",
	"win_score",
	"ball_size",
	NULL
};

static GConfClient *gconf_client = NULL;

void pong_properties_init (void);
PongProperties* pong_properties_load (void);
void pong_properties_save (PongProperties *prop);

void pong_properties_reset_default (void);

#endif
