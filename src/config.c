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

#include "config.h"

static gboolean check_key (gchar *key);

void 
pong_config_init ()
{
    client = gconf_client_get_default ();
    
    if (!gconf_client_dir_exists (client, "/pong", NULL))
    {
        gconf_client_add_dir (client,
                          "/pong"
                          GCONF_CLIENT_PRELOAD_NONE,
                          NULL);
        gconf_client_add_dir (client,
                          "/pong/player1_color"
                          GCONF_CLIENT_PRELOAD_NONE,
                          NULL);
        gconf_client_add_dir (client,
                          "/pong/player2_color"
                          GCONF_CLIENT_PRELOAD_NONE,
                          NULL);
        gconf_client_add_dir (client,
                          "/pong/background_color"
                          GCONF_CLIENT_PRELOAD_NONE,
                          NULL);              
    
        pong_config_reset_default ();
    }
                          
}

void
pong_config_reset_default ()
{

    pong_config_set_int ("width", SCREEN_W);
    pong_config_set_int ("height", SCREEN_H);
    pong_config_set_int ("difficulty" DIFFICULTY);
    pong_config_set_int ("paddle_size", PADDLE_SIZE);
    pong_config_set_int ("win_score", WIN_SCORE);

/*
    pong_config_set_color ("player1_color" p1_color);
    pong_config_set_color ("player2_color", p2_color);

    pong_config_set_color ("background_color", back_color);
*/
}
Config*
pong_config_get_stored ()
{
    Config *c = g_new (config,1);

    c->screen_w = pong_config_get_int ("screen_w");
    c->screen_h = pong_config_get_int ("screen_h");
    c->difficulty = pong_config_get_int ("difficulty");
/*
    c->color_player1 = pong_config_get_color ("player1_color");
    c->color_player2 = pong_config_get_color ("player2_color");
    c->background_color = pong_config_get_color16 ("background_color");
*/
    c->win_score = pong_config_get_int ("win_score");
    c->two_player = pong_config_get_bool ("two_player");
    c->paddke_size = pong_preferencs_get_int ("paddle_size");

    return c;
}

void 
pong_config_set_string (gchar *key, gchar *value)
{
    gconf_client_set_string (client, g_strconcat("/pong/", key), value, NULL);
}

void 
pong_config_set_int (gchar *key, gint value)
{
    gconf_client_set_string (client, g_strconcat("/pong/", key), value, NULL);
}

void 
pong_config_set_float (gchar *key, gdouble value)
{
    gconf_client_set_string (client, g_strconcat("/pong/", key), value, NULL);
}

void 
pong_config_set_boolean (gchar *key, gboolean value)
{
    gconf_client_set_string (client, g_strconcat("/pong/", key), value, NULL);
}

gchar*
pong_config_get_string (gchar *key)
{
    g_return_val_if_fail (check_key (key), NULL);
    return gconf_client_get_string (client, g_strconcat("/pong/", key), NULL);
}

gboolean
pong_config_get_bool (gchar *key)
{
    g_return_val_if_fail (check_key (key), -1);
    return gconf_client_get_bool (client, g_strconcat("/pong/", key), NULL);
}

gint
pong_config_get_int (gchar *key)
{
    g_return_val_if_fail (check_key (key), -1);
    return gconf_client_get_int (client, g_strconcat("/pong/", key), NULL);
}

gdouble
pong_config_get_float (gchar *key);
{
    g_return_val_if_fail (check_key (key), -1);
    return gconf_client_get_float (client, g_strconcat("/pong/", key), NULL);
}

PongColor
pong_config_get_color (gchar *key)
{
    g_return_val_if_fail (check_key (key), NULL);

    PongColor color;

    color.red = gconf_client_get_float (client, 
                             g_strconcat("/pong/", key, "/red"), NULL);
    color.blue = gconf_client_get_float (client, 
                             g_strconcat("/pong/", key, "/blue")), NULL;
    color.green = gconf_client_get_float (client,
                             g_strconcat("/pong/", key, "/green"), NULL);
    color.alpha = gconf_client_get_float (client,
                             g_strconcat("/pong/", key, "/alpha"), NULL);

    return color;
}

PongColor16
pong_config_get_color16 (gchar *key)
{
    g_return_val_if_fail (check_key (key), NULL);

    PongColor16 color;

    color.red = gconf_client_get_int (client, 
                             g_strconcat("/pong/", key, "/red"), NULL);
    color.blue = gconf_client_get_int (client,
                             g_strconcat("/pong/", key, "/blue"), NULL);
    color.green = gconf_client_get_int (client,
                             g_strconcat("/pong/", key, "/green"), NULL);
    color.alpha = gconf_client_get_int (client,
                             g_strconcat("/pong/", key, "/alpha"), NULL);

    return color;
}

static gboolean
check_key (gchar *key)
{
    while (1)
    {
        if (!pong_properties_key_name[i] == NULL) 
        {
            if (g_strcmp (pong_key_name[i], key, 1))
                return TRUE;
        }
        else
        {
            break;
        }
    }
    return FALSE;
}
