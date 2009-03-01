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
#include "scoreboard.h"

GtkWidget *label_p1;
GtkWidget *label_p2;

Scoreboard* 
pong_scoreboard_new (GtkWidget *statusbar)
{
    Scoreboard *sb = g_new (Scoreboard,1);
    sb->score_p1 = 0;
    sb->score_p2 = 0; 
    
    GtkWidget *hbox = gtk_hbox_new (FALSE, 8);
    gtk_widget_show (hbox);

    label_p1 = gtk_label_new ("");
    label_p2 = gtk_label_new ("");
    
    gtk_box_pack_start (GTK_BOX (hbox), label_p1, FALSE, FALSE, 0);
    gtk_box_pack_end (GTK_BOX (hbox), label_p2, FALSE, FALSE, 0);

    gtk_box_pack_start (GTK_BOX (statusbar), hbox, FALSE, FALSE, 4);

    gtk_widget_show (label_p2);
    gtk_widget_show (label_p1);

    pong_scoreboard_clear (sb);

    return sb;
}

void
pong_scoreboard_update (Scoreboard *sb)
{
    gchar sc1[45];
    gchar sc2[45];
    sprintf (sc1, "Player One: %o", sb->score_p1);
    sprintf (sc2, "Player Two: %o", sb->score_p2);
    gtk_label_set_text (GTK_LABEL (label_p1), sc1);
    gtk_label_set_text (GTK_LABEL (label_p2), sc2);
}

void
pong_scoreboard_clear (Scoreboard *sb)
{
    sb->score_p1 = 0;
    sb->score_p2 = 0;

    gtk_label_set_text (GTK_LABEL (label_p1), "");
    gtk_label_set_text (GTK_LABEL (label_p2), "");

}
