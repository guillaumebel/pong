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
 
#ifndef PONG_H_
#define PONG_H_

#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>
#include <gdk/gdkkeysyms.h>

#include "scoreboard.h"
#include "paddle.h"
#include "ball.h"

#include "properties.h"

#include "preferences.h"

typedef struct PongGame {
    Paddle *p1;
    Paddle *p2;
    Ball *ball;

    int player1_y; 
    int player2_y; 
    
    float speed;

    int endgame;
    gboolean paused;
} PongGame;


static GtkWidget *window = NULL;
static ClutterTimeline *timeline = NULL;
static ClutterActor *message_label = NULL;

static Config* config = NULL;

static Scoreboard *sb = NULL;
static PongGame *game = NULL;

static GtkAction *fullscreen_action;

static const char ui_description[] =
  "<ui>"
  "  <menubar name='MainMenu'>"
  "    <menu action='GameMenu'>"
  "      <menuitem action='NewGame'/>"
  "      <menuitem action='EndGame'/>"
  "      <separator/>"
  "      <menuitem action='Pause'/>"
  "      <menuitem action='Resume'/>"
  "      <separator/>"
  "      <menuitem action='Scores'/>"
  "      <separator/>"
  "      <menuitem action='Quit'/>"
  "    </menu>"
  "    <menu action='ViewMenu'>"
  "      <menuitem action='Fullscreen'/>"
  "      <menuitem action='LeaveFullscreen'/>"
  "    </menu>"
  "    <menu action='SettingsMenu'>"
  "      <menuitem action='Preferences'/>"
  "    </menu>"
  "    <menu action='HelpMenu'>"
  "      <menuitem action='About'/>" 
  "    </menu>" 
  "  </menubar>" 
  "</ui>";
 

#endif
