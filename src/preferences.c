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

static gint
pong_preferences_cb (GtkAction * action, gpointer data)
{
    GtkWidget *window;
    GtkWidget *vbox1;
    GtkWidget *vbox2;
    GtkWidget *vbox3;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;

    GtkWidget *notebook;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    notebook = gtk_notebook_new ();

    

    label1 = gtk_label_new ("General");
    label2 = gtk_label_new ("Player one");
    label3 = gtk_label_new ("player two");

    gtk_notebook_append_page (notebook, vbox1, label1);
    gtk_notebook_append_page (notebook, vbox2, label2);
    gtk_notebook_append_page (notebook. vbox3, label3);


    gtk_container_add (GTK_CONTAINER (window), notebook);
    
    vbox = gtk_vbox_new (TRUE, 6);

    return 0;
}  
