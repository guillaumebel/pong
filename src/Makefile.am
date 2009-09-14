INCLUDES = \
	-I$(SRCDIR) \
	-Wall \
	$(CLUTTER_CFLAGS) \
	$(CLUTTER_GTK_CFLAGS) \
	$(GTK_CFLAGS) \
	$(GCONF_CFLAGS)
	
bin_PROGRAMS = pong
pong_SOURCES = pong.c \
               paddle.c \
               ball.c \
               scoreboard.c \
			   			 properties.c \
			   			 preferences.c \
							 main.c
               
pong_LDADD = $(GTK_LIBS) \
						 $(CLUTTER_LIBS) \
		 				 $(CLUTTER_GTK_LIBS) \
						 $(GCONF_LIBS)

