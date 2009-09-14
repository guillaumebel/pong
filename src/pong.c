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
 
#include <gdk/gdk.h>
#include <clutter-gtk/clutter-gtk.h>
#include <clutter/clutter.h>
#include "paddle.h"
#include "ball.h"
#include "pong.h"

GdkPixbuf *pong_pixbuf[3] = {NULL, NULL, NULL};

extern PongGame *game;
extern PongProperties *properties;

static GdkPixbuf*
pong_load_pixmap_file (const gchar* pixmap, gint xsize, gint ysize)
{
  GdkPixbuf *image;
  gchar *filename;
  const char *dirname;
  dirname = "../pix";
  filename = g_build_filename (dirname, pixmap, NULL);

  image = gdk_pixbuf_new_from_file_at_scale (filename, xsize, ysize, TRUE, NULL);
  g_free (filename);

  return image;
}

static void
pong_load_pixbuf (void)
{
  gchar *pixbuf_files[] = {
	  "ball_green.svg",
	  "paddle_blue.svg",
	  "paddle_red.svg"
  };

  pong_pixbuf[0] = pong_load_pixmap_file (pixbuf_files[0],
										                     2 * BALL_NORMAL,
										                     2 * BALL_NORMAL);
  pong_pixbuf[1] = pong_load_pixmap_file (pixbuf_files[1], 
										                     2 * PADDLE_NORMAL_W,
										                     2 * PADDLE_NORMAL_H);
  pong_pixbuf[2] = pong_load_pixmap_file (pixbuf_files[2], 
										                     2 * PADDLE_NORMAL_W,
										                     2 * PADDLE_NORMAL_H);
}

void
pong_init (void) 
{
	game = g_new (PongGame, 1);	
	game->p1 = pong_paddle_new ();
	game->p2 = pong_paddle_new ();
	game->ball = pong_ball_new ();

	switch (properties->paddle_size) {
		case 1:
			pong_paddle_set_size (game->p1, PADDLE_TINY_W, PADDLE_TINY_H);
			pong_paddle_set_size (game->p2, PADDLE_TINY_W, PADDLE_TINY_H);
			break;
		case 3:
			pong_paddle_set_size (game->p1, PADDLE_BIG_W, PADDLE_BIG_H);
			pong_paddle_set_size (game->p1, PADDLE_BIG_W, PADDLE_BIG_H);
			break;
		default:
			break;
	}
	
	switch (properties->ball_size) {
		case 1:
			pong_ball_set_size (game->ball, BALL_TINY);
			break;
		case 3:
			pong_ball_set_size (game->ball, BALL_BIG);
			break;
		default:
			break;
	}

	game->speed = 1.0;

	game->player1_y = SCREEN_H / 2 - PADDLE_NORMAL_H / 2;
	game->player2_y = SCREEN_H / 2 - PADDLE_NORMAL_H / 2;	

	game->endgame = FALSE;
	game->paused = FALSE;
}


