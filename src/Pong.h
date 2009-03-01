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
#include <clutter-cairo/clutter-cairo.h>
#include <clutter-gtk/gtk-clutter-embed.h>
#include <gdk/gdkkeysyms.h>

#include "scoreboard.h"
#include "paddle.h"
#include "ball.h"

#define REBOND 7    // rebond limit

typedef struct PongGame {
    Paddle *p1;
    Paddle *p2;
    Ball *ball;

    int player1_y; 
    int player2_y; 
    
    int two_player;
    float speed;

    int endgame;
    gboolean paused;
    
    int screen_w;
    int screen_h;
} PongGame;

typedef struct Config {
    int screen_w;
    int screen_h;
    float speed; //difficulty easy, medium. hard
    ClutterColor *color_player1;
    ClutterColor *color_player2;
    ClutterColor *background_color;
    int win_score;
    gboolean two_player;
    int paddle_size; //tiny, normal, big 

} Config;

GtkWidget *window = NULL;
ClutterTimeline *timeline = NULL;
ClutterActor *message_label = NULL;

Scoreboard *sb = NULL;
PongGame *game = NULL;

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
