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

#include "properties.h"

static gboolean check_key (gchar *key);

void 
pong_properties_init (void)
{
	GError *gconf_error = NULL;
	gconf_client = gconf_client_get_default ();
	
	if (!gconf_client_dir_exists (gconf_client, GCONF_DIR, &gconf_error))	{
		gconf_client_add_dir (gconf_client,
						              GCONF_DIR,
						              GCONF_CLIENT_PRELOAD_NONE,
            						  &gconf_error);
		if (gconf_error) {
			g_warning ("Unable to acces GConf: %s\n", gconf_error->message);
			g_error_free (gconf_error);
		} else 
			pong_properties_reset_default (); 

	}   
}

void
pong_properties_reset_default (void)
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
	gconf_client_set_int (gconf_client,
						            BALLSIZE_KEY,
					          	  2,
          						  NULL);
}

PongProperties*
pong_properties_load (void)
{
	PongProperties *prop = g_new (PongProperties,1);

	prop->screen_w = gconf_client_get_int (gconf_client,
			                                   WIDTH_KEY, NULL);
	prop->screen_h = gconf_client_get_int (gconf_client,
						                             HEIGHT_KEY, NULL);
	prop->difficulty = gconf_client_get_int (gconf_client,
						                               DIFFICULTY_KEY, NULL);
	prop->win_score = gconf_client_get_int (gconf_client,
						                              WINSCORE_KEY, NULL);
	prop->two_player = gconf_client_get_int (gconf_client,
						                               TWOPLAYER_KEY, NULL);
	prop->paddle_size = gconf_client_get_int (gconf_client,
						                                PADDLESIZE_KEY, NULL);
	prop->ball_size = gconf_client_get_int (gconf_client,
						                              BALLSIZE_KEY, NULL);
	return prop;
}

void
pong_properties_save (PongProperties *prop)
{
	gconf_client_set_int (gconf_client,
				          		  WIDTH_KEY,
	          					  prop->screen_w,
						            NULL);
	gconf_client_set_int (gconf_client,
		          				  HEIGHT_KEY,
          						  prop->screen_h,
				          		  NULL);
	gconf_client_set_int (gconf_client,
			          			  DIFFICULTY_KEY,
		          				  prop->difficulty,
						            NULL);
	gconf_client_set_int (gconf_client,
          						  WINSCORE_KEY,
					          	  prop->win_score,
						            NULL);
	gconf_client_set_int (gconf_client,
          						  TWOPLAYER_KEY,
					          	  prop->two_player,
					          	  NULL);
	gconf_client_set_int (gconf_client,
		          				  PADDLESIZE_KEY,
						            prop->paddle_size,
						            NULL);
	gconf_client_set_int (gconf_client,
          						  BALLSIZE_KEY,
					          	  prop->ball_size,
						            NULL);

}

static gboolean
check_key (gchar *key)
{
	int i;

	while (1)	{
		if (pong_key_name[i]) {
			if (strcmp (pong_key_name[i], key) == 0)
				return TRUE;
			
			i++;
		} else {
			break;
		}
	}
	return FALSE;
}
