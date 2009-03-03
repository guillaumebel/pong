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
    GError *gconf_error = NULL;

    gconf_client = gconf_client_get_default ();
    
    if (!gconf_client_dir_exists (gconf_client, GCONF_DIR, &gconf_error))
    {


        gconf_client_add_dir (gconf_client,
                          GCONF_DIR,
                          GCONF_CLIENT_PRELOAD_NONE,
                          &gconf_error);
/*
        gconf_client_add_dir (gconf_client,
                          "/apps/pong/player1_color",
                          GCONF_CLIENT_PRELOAD_NONE,
                          &gconf_error);
        gconf_client_add_dir (gconf_client,
                          "/apps/pong/player2_color",
                          GCONF_CLIENT_PRELOAD_NONE,
                          &gconf_error);
        gconf_client_add_dir (gconf_client,
                          "/apps/pong/background_color",
                          GCONF_CLIENT_PRELOAD_NONE,
                          &gconf_error);              

*/
        if (gconf_error)
        {
            g_warning ("Unable to acces GConf: %s\n", gconf_error->message);
            g_error_free (gconf_error);
        }
        else 
        {
            pong_config_reset_default ();
        }
    }
                          
}

void
pong_config_reset_default ()
{
    gconf_client_set_int (gconf_client,
                          WIDTH_KEY,
                          SCREEN_W,
                          NULL);
    gconf_client_set_int (gconf_client,
                          HEIGHT_KEY,
                          SCREEN_H,
                          NULL);
    gconf_client_set_int (gconf_client,
                          DIFFICULTY_KEY,
                          DIFFICULTY,
                          NULL);
    gconf_client_set_int (gconf_client,
                          WINSCORE_KEY,
                          WIN_SCORE,
                          NULL);
    gconf_client_set_int (gconf_client,
                          TWOPLAYER_KEY,
                          TWO_PLAYER,
                          NULL);
    gconf_client_set_int (gconf_client,
                          PADDLESIZE_KEY,
                          2,
                          NULL); 
}

Config*
pong_config_load ()
{
    Config *c = g_new (Config,1);
    c->screen_w = gconf_client_get_int (gconf_client,
                          WIDTH_KEY, NULL);
    c->screen_h = gconf_client_get_int (gconf_client,
                          HEIGHT_KEY, NULL);
    c->difficulty = gconf_client_get_int (gconf_client,
                          DIFFICULTY_KEY, NULL);
    c->win_score = gconf_client_get_int (gconf_client,
                          WINSCORE_KEY, NULL);
    c->two_player = gconf_client_get_int (gconf_client,
                          TWOPLAYER_KEY, NULL);
    c->paddle_size = gconf_client_get_int (gconf_client,
                          PADDLESIZE_KEY, NULL);
                          
    return c;
}

void
pong_config_save (Config *c)
{
    gconf_client_set_int (gconf_client,
                          WIDTH_KEY,
                          c->screen_w,
                          NULL);
    gconf_client_set_int (gconf_client,
                          HEIGHT_KEY,
                          c->screen_h,
                          NULL);
    gconf_client_set_int (gconf_client,
                          DIFFICULTY_KEY,
                          c->difficulty,
                          NULL);
    gconf_client_set_int (gconf_client,
                          WINSCORE_KEY,
                          c->win_score,
                          NULL);
    gconf_client_set_int (gconf_client,
                          TWOPLAYER_KEY,
                          c->two_player,
                          NULL);
    gconf_client_set_int (gconf_client,
                          PADDLESIZE_KEY,
                          c->paddle_size,
                          NULL);               

}


PongColor
pong_config_get_color (gchar *key)
{
    PongColor color;

    g_return_val_if_fail (check_key (key), color);

    color.red = gconf_client_get_float (gconf_client, 
                             g_strconcat("/apps/pong/", key, "/red"), NULL);
    color.blue = gconf_client_get_float (gconf_client, 
                             g_strconcat("/apps/pong/", key, "/blue"), NULL);
    color.green = gconf_client_get_float (gconf_client,
                             g_strconcat("/apps/pong/", key, "/green"), NULL);
    color.alpha = gconf_client_get_float (gconf_client,
                             g_strconcat("/apps/pong/", key, "/alpha"), NULL);

    return color;
}

PongColor16
pong_config_get_color16 (gchar *key)
{

    PongColor16 color;

    g_return_val_if_fail (check_key (key), color );
    
    color.red = gconf_client_get_int (gconf_client, 
                             g_strconcat("/apps/pong/", key, "/red"), NULL);
    color.blue = gconf_client_get_int (gconf_client,
                             g_strconcat("/apps/pong/", key, "/blue"), NULL);
    color.green = gconf_client_get_int (gconf_client,
                             g_strconcat("/apps/pong/", key, "/green"), NULL);
    color.alpha = gconf_client_get_int (gconf_client,
                             g_strconcat("/apps/pong/", key, "/alpha"), NULL);

    return color;
}

static gboolean
check_key (gchar *key)
{
    int i;

    while (1)
    {
        if (!pong_key_name[i] == NULL) 
        {
            if (strcmp (pong_key_name[i], key) == 0)
                return TRUE;
            
            i++;
        }
        else
        {
            break;
        }
    }
    return FALSE;
}
