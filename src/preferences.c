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

#include "preferences.h"

static void
destroy_cb (GtkWidget *widget, gpointer data)
{
    pref_dialog = NULL;
}

static void
apply_cb (GtkWidget *widget, gpointer data)
{
    pong_config_save (config);
    gtk_widget_destroy (widget);
}

static void
difficulty_cb (GtkWidget *widget, gpointer data)
{
    if (GTK_TOGGLE_BUTTON (widget)->active)
    {
        config->difficulty = GPOINTER_TO_INT (data);
    }
}

static void
paddle_size_cb (GtkWidget *widget, gpointer data)
{
    if (GTK_TOGGLE_BUTTON (widget)->active)
    {
        config->paddle_size = GPOINTER_TO_INT (data);
    }
}

gint
pong_preferences_cb (GtkAction * action, gpointer data)
{

    GtkWidget *vbox;
    GtkWidget *label1;

    GtkWidget *table;
    GtkWidget *frame;
    GtkWidget *button;

    PangoAttrList *attr_list;
    PangoAttribute *attr;

    attr_list = pango_attr_list_new ();
    attr = pango_attr_weight_new (PANGO_WEIGHT_BOLD);
    attr->start_index = 0;
    attr->end_index = -1;
    pango_attr_list_insert(attr_list, attr);

    GtkWidget *notebook;

    if (config == NULL)
    {
        pong_config_init ();
        config = pong_config_load ();
    }

    pref_dialog = gtk_dialog_new_with_buttons ("Pong Preferences",
                            GTK_WINDOW (window), 0,
                            GTK_STOCK_CLOSE,
                            GTK_RESPONSE_CLOSE, NULL);

    gtk_dialog_set_has_separator (GTK_DIALOG (pref_dialog), FALSE);
    gtk_container_set_border_width (GTK_CONTAINER (pref_dialog), 5);
    gtk_box_set_spacing (GTK_BOX (GTK_DIALOG (pref_dialog)->vbox), 2);

    notebook = gtk_notebook_new ();
    gtk_container_set_border_width (GTK_CONTAINER (notebook), 5);

    gtk_container_add (GTK_CONTAINER (GTK_DIALOG (pref_dialog)->vbox), 
                        notebook);
 
    label1 = gtk_label_new ("General");
    table = gtk_table_new (1,2, FALSE);
    gtk_table_set_col_spacings(GTK_TABLE (table), 18);
    gtk_container_set_border_width (GTK_CONTAINER (table), 12);

    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), table, label1);

    frame = gtk_frame_new ("Difficulty");
    gtk_label_set_attributes (GTK_LABEL (
                             gtk_frame_get_label_widget (GTK_FRAME(frame))), 
                             attr_list);

    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);

    gtk_table_attach (GTK_TABLE (table), frame, 0,1,0,1,0, 
                                        GTK_FILL | GTK_EXPAND, 0, 0);

    vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (frame), vbox);

    button = gtk_radio_button_new_with_label (NULL, "Easy");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 3);
    
    if (config->difficulty == 1)
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    
    g_signal_connect (GTK_OBJECT (button), "toggled", 
                            G_CALLBACK (difficulty_cb), (gpointer)1);

    button = gtk_radio_button_new_with_label (
                        gtk_radio_button_get_group (GTK_RADIO_BUTTON (button)),
                        "Medium");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 3);
    
    if (config->difficulty == 2)
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    
    g_signal_connect (GTK_OBJECT (button), "toggled", 
                            G_CALLBACK (difficulty_cb), (gpointer)2);

    button = gtk_radio_button_new_with_label (
                        gtk_radio_button_get_group (GTK_RADIO_BUTTON (button)),
                        "Hard");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 3);
    
    if (config->difficulty == 3)
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    
    g_signal_connect (GTK_OBJECT (button), "toggled",
                            G_CALLBACK (difficulty_cb), (gpointer)3);



    frame = gtk_frame_new ("Paddle size");
    gtk_label_set_attributes (GTK_LABEL (
                              gtk_frame_get_label_widget (GTK_FRAME(frame))), 
                              attr_list);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);

    gtk_table_attach_defaults (GTK_TABLE (table), frame, 1, 2, 0, 1);
    vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (frame), vbox);

    button = gtk_radio_button_new_with_label (NULL, "Tiny");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 3);
    
    if (config->paddle_size == 1)
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    
    g_signal_connect (GTK_OBJECT (button), "toggled", 
                            G_CALLBACK (paddle_size_cb), (gpointer)1);


    button = gtk_radio_button_new_with_label (
                        gtk_radio_button_get_group (GTK_RADIO_BUTTON (button)),
                        "Normal");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 3);
    
    if (config->paddle_size == 2)
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    
    g_signal_connect (GTK_OBJECT (button), "toggled", 
                            G_CALLBACK (paddle_size_cb), (gpointer)2);

    button = gtk_radio_button_new_with_label (
                        gtk_radio_button_get_group (GTK_RADIO_BUTTON (button)),
                        "Big");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 3);
    
    if (config->paddle_size == 3)
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    
    g_signal_connect (GTK_OBJECT (button), "toggled",
                            G_CALLBACK (paddle_size_cb), (gpointer)3);



    gtk_widget_show_all (pref_dialog);

    g_signal_connect (G_OBJECT (pref_dialog), "response",
                        G_CALLBACK (apply_cb), NULL);
    g_signal_connect (G_OBJECT (pref_dialog), "destroy",
                        G_CALLBACK (destroy_cb), NULL);
    g_signal_connect (G_OBJECT (pref_dialog), "close",
                        G_CALLBACK (destroy_cb), NULL);

    return 0;
}  
