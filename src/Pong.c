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
 
#include "Pong.h"

static void
init_game () 
{
    game = g_new (PongGame, 1);    
    game->p1 = pong_paddle_new ();
    game->p2 = pong_paddle_new ();
    game->ball = pong_ball_new ();

    switch (config->paddle_size) 
    {
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
    
    switch (config->ball_size)
    {
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

static void
start_game ()
{
    if (clutter_timeline_is_playing (timeline))
    {
        game->endgame = FALSE;
    }
    else
    {
        clutter_timeline_start (timeline);
    }
}

static void 
message_label_show (gchar *message) 
{    
    clutter_label_set_text (CLUTTER_LABEL (message_label), message);
    clutter_actor_set_position (message_label, (config->screen_w / 2) 
                - (clutter_actor_get_width (CLUTTER_ACTOR (message_label)) / 2),
                (config->screen_h / 2)
                - (clutter_actor_get_height (CLUTTER_ACTOR (message_label)) / 2));
    clutter_actor_show (message_label);
}

static void
quit_cb (GObject * object, gpointer data)
{
    gtk_widget_destroy (window);
}

static void
fullscreen_cb (GtkAction * action, gpointer data)
{
    if (action == fullscreen_action)
    {
        gtk_window_fullscreen (GTK_WINDOW (window));
    }
    else 
    {
        gtk_window_unfullscreen (GTK_WINDOW (window));
    }
}

static gboolean
window_state_cb (GtkWidget * widget, GdkEventWindowState * event)
{    
      return FALSE;
}

static void
new_game_cb (GtkAction * action, gpointer data)
{
    start_game ();
}

static gint
delete_cb (GtkWidget * widget, gpointer data)
{
    gtk_widget_destroy (window);
    return FALSE;
}

static void
about_cb (GtkAction * action, gpointer data)
{
    const gchar *authors[] = { "Guillaume Beland", NULL };

    const gchar *documenters[] = { "Guillaume Beland", NULL };
    
    gchar *license = "Pong! is free software; you can redistribute it and/or "
    "modify it under the terms of the GNU General Public License as published by"
    "the Free Software Foundation; either version 2 of the License, or"
    "(at your option) any later version.\n"
    "Pong! is distributed in the hope that it will be useful,"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of "
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
    "GNU General Public License for more details. \n"
    "You should have received a copy of the GNU General Public License "
    "along with this program; if not, write to the Free Software Foundation, "
    "Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.";

    gtk_show_about_dialog (GTK_WINDOW (window), 
                             "name", "Pong", \
                             "version", "1.0", 
                             "copyright", 
                             "Copyright \xc2\xa9 2009 Guillaume Béland", 
                             "license", license, "comments", 
                             "A simple pong game", "authors", authors, 
                             "documenters", documenters, "translator-credits", 
                             "translator-credits", "logo-icon-name", 
                             "Pong", "website", 
                             "http://damino.ca/pong", 
                             "website-label", "Pong website", 
                             "wrap-license", TRUE, NULL);
             
}

static gint
pause_game_cb (GtkAction * action, gpointer data)
{
    if (game->paused)
    {
        game->paused = FALSE;
        clutter_actor_hide (message_label);
    }
    else
    {
        game->paused = TRUE;
        message_label_show ("Paused");
    }    
    return game->paused;
}

static void
show_scores_cb (GtkAction * action, gpointer data)
{
}

static gint
end_game_cb (GtkAction * action, gpointer data)
{
    pong_ball_set_position (game->ball, config->screen_w / 2, config->screen_h /2);
    pong_scoreboard_clear (sb);
    
    game->player1_y = SCREEN_H / 2 - PADDLE_NORMAL_H / 2;
    game->player2_y = SCREEN_H / 2 - PADDLE_NORMAL_H / 2;   

    pong_paddle_set_position (game->p1, 6, game->player1_y);
    pong_paddle_set_position (game->p2, config->screen_w - 10, game->player2_y);

    clutter_actor_hide (message_label);
    game->paused = FALSE;
    return game->endgame = TRUE;
}

static void 
window_resize_cb (GtkWidget *widget, GtkRequisition *req, gpointer data) 
{   
    gtk_window_get_size (GTK_WINDOW (window), &config->screen_w, &config->screen_h);
    clutter_actor_set_size ((ClutterActor*)data, config->screen_w, config->screen_h);
}

static void
on_timeline_new_frame (ClutterTimeline *timeline, gint frame_num, gpointer data)
{    
    if (game->endgame) 
        return;

    if (game->paused)
        return;
        
    //Check collision with walls
    if (game->ball->y <= game->ball->size \
        || game->ball->y >= config->screen_h - game->ball->size) 
    {
        game->ball->vspeed = -game->ball->vspeed;
        game->ball->y = (game->ball->y > config->screen_h / 2 
                  ? config->screen_h - (game->ball->size * 2) : game->ball->size * 2);
    }
    
    //collision with paddles
    if (game->ball->x <= (REBOND + game->p1->width * 2 - 1) 
        && game->ball->x >= REBOND 
        && game->ball->y >= game->player1_y  
        && game->ball->y <= game->player1_y + game->p1->size)
    {
        game->ball->hspeed = -game->ball->hspeed;
        game->ball->vspeed = game->ball->speed 
                          * sin (atan (game->ball->vspeed / game->ball->hspeed 
                          + (game->ball->y - game->player1_y) 
                          / (game->p1->size / 2)));
                       
        game->ball->hspeed = (game->ball->hspeed / abs (game->ball->hspeed)) 
                          * game->ball->speed * cos (asin (game->ball->vspeed 
                          / game->ball->speed));
        
        game->ball->x += game->ball->hspeed;
    }
    
    if (game->ball->x >= config->screen_w - (REBOND + game->p2->width * 2 - 1) 
        && game->ball->x <= config->screen_w - REBOND 
        && game->ball->y >= game->player2_y - game->p2->size / 2
        && game->ball->y <= game->player2_y + game->p2->size)
    {
        game->ball->hspeed = -game->ball->hspeed;
        game->ball->vspeed = game->ball->speed 
                          * sin (atan (game->ball->vspeed / game->ball->hspeed 
                          + (game->ball->y - game->player2_y) 
                          / (game->p2->size / 2)));

        game->ball->hspeed = (game->ball->hspeed /abs (game->ball->hspeed)) 
                          * game->ball->speed * cos (asin (game->ball->vspeed 
                          / game->ball->speed));
        
        game->ball->x += game->ball->hspeed ;
    }
    
    //point marking    
    if (game->ball->x <= 0)
    {
        sb->score_p2++;
        pong_scoreboard_update (sb);
        game->ball->x = config->screen_w / 2;
        game->ball->y = config->screen_h / 2;
    }
    
    if (game->ball->x >= config->screen_w - 4) 
    {
        sb->score_p1++;
        pong_scoreboard_update (sb);
        game->ball->x = config->screen_w / 2;
        game->ball->y = config->screen_h / 2;
    }
    
    // AI
    if (!config->two_player) 
    {
        if (game->ball->hspeed > 0 && game->ball->x >= (config->screen_h - config->screen_w / 4 
            * (game->ball->hspeed / game->ball->speed)))
        {
            if (game->ball->y > (game->player2_y + game->p2->size / 2) 
                && game->player2_y < (config->screen_h - game->p2->size / 2)) 
            {
                game->player2_y += game->p1->speed;
            } 
            else if (game->ball->y < (game->player2_y-game->p2->size/2)
                       && game->player2_y > game->p2->size / 2) 
            {       
                game->player2_y -= game->p2->speed;
            }
        }
    }
        
    game->ball->x += game->ball->hspeed;
    game->ball->y += game->ball->vspeed;
    
    pong_ball_set_position (game->ball, 
                                game->ball->x, game->ball->y);
    pong_paddle_set_position (game->p2, 
                                config->screen_w - 10, game->player2_y);
}

static gboolean
key_press_cb (ClutterActor *actor, ClutterEvent *event, gpointer data)
{
    //pause and unpause the game
    if (event->type == CLUTTER_KEY_PRESS)
    {    
        if (GDK_p == event->key.keyval)
        {
            if (game->paused)
            {
                clutter_actor_hide (message_label);
                return game->paused = FALSE;
            }    
            else
            {
                message_label_show ("Paused");
                return game->paused = TRUE;
            }
        }
    }
    
    //if paused don nothing
    if (game->paused || game->endgame)
        return FALSE;
    
    // Move the p1    
    if (event->type == CLUTTER_KEY_PRESS)
    {        
        if (GDK_Up == event->key.keyval && game->player1_y >= 1)
        {
            game->player1_y -= game->p1->speed * 3;
            pong_paddle_set_position (game->p1, 6, game->player1_y);
        }
        if (GDK_Down == event->key.keyval 
            && game->player1_y <= (config->screen_h - game->p1->size))
        {
            game->player1_y += game->p1->speed * 3;
            pong_paddle_set_position (game->p1, 6, game->player1_y);
        }

        if (config->two_player)
        {
            if (GDK_a == event->key.keyval && game->player2_y >= 1)
            {
                game->player2_y -= game->p2->speed * 3;
                pong_paddle_set_position (game->p2, 6, game->player2_y);
            }
            if (GDK_z == event->key.keyval 
                && game->player1_y <= (config->screen_h - game->p2->size))
            {
                game->player2_y += game->p2->speed * 3;
                pong_paddle_set_position (game->p2, 6, game->player2_y);
            }
        }
    }
    return TRUE;
}

static gboolean
on_stage_motion_event_cb (ClutterActor *actor, ClutterEvent *event, gpointer data)
{
    ClutterMotionEvent *mev = (ClutterMotionEvent *)event;

    if (game->player1_y >= 1 && game->player1_y <= (config->screen_h - game->p1->size))
    {
        game->player1_y = mev->y;
        pong_paddle_set_position (game->p1, 6, mev->y);
    }

    return TRUE;
}

int 
main (int argc, char **argv) 
{

    gtk_clutter_init (&argc, &argv);

    if (config == NULL)
    {
        pong_config_init ();
        config = pong_config_load ();
    }
    init_game ();
    
    //Clutter declaration
    ClutterActor *background = NULL;
    ClutterActor *stage = NULL;
    ClutterColor stage_color = {0x01, 0x05, 0x1e, 0xff};
    ClutterColor label_color = {0xFF, 0xFF, 0xFF, 0xff};

    //Gtk declaration
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *vbox = gtk_vbox_new (FALSE,6);
    GtkWidget *clutter_widget = gtk_clutter_embed_new ();    
    GtkWidget *statusbar = gtk_statusbar_new ();

    // Menu stuff
    GtkWidget *menubar;
    GtkUIManager *ui_manager = gtk_ui_manager_new ();
    GtkAccelGroup *accel_group;    
    GtkActionGroup *action_group;

    const GtkActionEntry action_entry[] = {
        {"GameMenu", NULL, "_Game"},
        {"ViewMenu", NULL, "_View"},
        {"SettingsMenu", NULL, "_Settings"},
        {"HelpMenu", NULL, "_Help"},
        {"NewGame", GTK_STOCK_NEW, "_New Game" , NULL, NULL,
        G_CALLBACK (new_game_cb)},
        {"Pause", GTK_STOCK_MEDIA_PAUSE, "_Pause", NULL, NULL,
        G_CALLBACK (pause_game_cb)},
        {"Resume", NULL, "_Resume", NULL, NULL,
        G_CALLBACK (pause_game_cb)},
        {"EndGame", GTK_STOCK_MEDIA_STOP, "_End Game", NULL, NULL,
        G_CALLBACK (end_game_cb)},
        {"Scores", NULL, "_Scores", NULL, NULL,
        G_CALLBACK (show_scores_cb)},
        {"Quit", GTK_STOCK_QUIT, "_Quit", NULL, NULL, G_CALLBACK (quit_cb)},
        {"Fullscreen", GTK_STOCK_FULLSCREEN, "_Fullscreen", NULL, NULL,
        G_CALLBACK (fullscreen_cb)},
        {"LeaveFullscreen", GTK_STOCK_FULLSCREEN, "_Leave Fullscreen",NULL,NULL,
        G_CALLBACK (fullscreen_cb)},
        {"Preferences", GTK_STOCK_PREFERENCES, "_Preferences", NULL, NULL,
        G_CALLBACK (pong_preferences_cb)},
        {"About", GTK_STOCK_ABOUT, "_About", NULL, NULL, G_CALLBACK (about_cb)}
    };

    action_group = gtk_action_group_new ("group");

    gtk_action_group_add_actions (action_group, action_entry,
                G_N_ELEMENTS (action_entry), game);

    gtk_ui_manager_insert_action_group (ui_manager, action_group, 0);
    gtk_ui_manager_add_ui_from_string (ui_manager, ui_description, - 1, NULL);

    // some more gtk stuff
    gtk_window_set_title (GTK_WINDOW (window), "Pong!");

    gtk_window_set_default_size (GTK_WINDOW (window), config->screen_w, config->screen_h + 50);

    accel_group = gtk_ui_manager_get_accel_group (ui_manager);
    gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

    menubar = gtk_ui_manager_get_widget (ui_manager, "/MainMenu");    

    sb = pong_scoreboard_new (statusbar);

    //packing stuff
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    gtk_box_pack_start (GTK_BOX (vbox), menubar, FALSE, FALSE, 0);
    
    gtk_box_pack_start (GTK_BOX (vbox), clutter_widget, TRUE, TRUE, 3);
    gtk_widget_show (clutter_widget);

    gtk_box_pack_end (GTK_BOX (vbox), statusbar, FALSE, FALSE, 0);
    gtk_widget_show (statusbar);
    
    //stage
    stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutter_widget));
    clutter_stage_set_color (CLUTTER_STAGE (stage), &stage_color);
    clutter_stage_set_user_resizable (CLUTTER_STAGE (stage), TRUE);
    clutter_stage_hide_cursor (CLUTTER_STAGE (stage));
    clutter_actor_show (stage);
    
    //texture
    
    background = clutter_texture_new_from_file ("back2.png",NULL);
    clutter_actor_set_position (background, 0, 0);
    clutter_actor_set_size (background, config->screen_w, config->screen_h);

    clutter_actor_set_opacity (background, 0xA9);
    clutter_container_add_actor (CLUTTER_CONTAINER (stage), background);
    clutter_actor_show (background);
    
    PongColor start;
    start.red = 0.95;
    start.green = 0.17;
    start.blue = 0.17;
    start.alpha = 0.75;

    PongColor stop;
    stop.red = 0.57;
    stop.green = 0.02;
    stop.blue = 0.02;
    stop.alpha = 0.75;


    //Paddle 1
    pong_paddle_set_size (game->p1, 
                            game->p1->width, game->p1->size);  
    pong_paddle_set_position (game->p1, 6, game->player1_y);
    
    clutter_container_add_actor (CLUTTER_CONTAINER (stage), 
                                         game->p1->actor);
    clutter_actor_show (game->p1->actor);

    //Paddle 2
    pong_paddle_set_size (game->p2, 
                            game->p2->width, game->p2->size);
    pong_paddle_set_position (game->p2, config->screen_w - 10, game->player2_y);


    pong_paddle_set_color (game->p2, start, stop);
    clutter_container_add_actor (CLUTTER_CONTAINER (stage), 
                                         game->p2->actor);
    clutter_actor_show (game->p2->actor);
    
    //ball
    pong_ball_set_size (game->ball, game->ball->size);
    pong_ball_set_position (game->ball, 
                                game->ball->x, game->ball->y);
    clutter_container_add_actor (CLUTTER_CONTAINER (stage), game->ball->actor);
    clutter_actor_show (game->ball->actor);
    
    //message label
    message_label = clutter_label_new_full ("Sans 26","", &label_color);
    clutter_container_add_actor (CLUTTER_CONTAINER (stage), message_label);

    //timeline
    timeline = clutter_timeline_new (10 , 120);
    clutter_timeline_set_loop(timeline, TRUE); 

    //callback connect
    g_signal_connect (stage, "motion-event", G_CALLBACK (on_stage_motion_event_cb), NULL);

    g_signal_connect (timeline, "new-frame", 
                            G_CALLBACK (on_timeline_new_frame), NULL);
    g_signal_connect (stage, "key-press-event", G_CALLBACK (key_press_cb), NULL);
    g_signal_connect (window, "hide", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (window), "destroy", 
                            G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                            G_CALLBACK (delete_cb), NULL);
    g_signal_connect (G_OBJECT (window), "window_state_event",
                            G_CALLBACK (window_state_cb), NULL);
    g_signal_connect (G_OBJECT (window), "size-request",
                            G_CALLBACK (window_resize_cb), background);
                            
    gtk_widget_show (GTK_WIDGET (window));

    gtk_main ();
    g_object_unref (timeline);

    return EXIT_SUCCESS;
}
