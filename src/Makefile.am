INCLUDES = \
	-I$(SRCDIR) \
	-Wall \
	$(CLUTTER_CFLAGS) \
	$(GTK_CFLAGS) \
	$(GCONF_CFLAGS)
	
bin_PROGRAMS = pong
pong_SOURCES = Pong.c \
               paddle.c \
               ball.c \
               scoreboard.c \
			   properties.c \
			   preferences.c
               
pong_LDADD = $(GTK_LIBS) \
	     $(CLUTTER_LIBS) \
		 $(GCONF_LIBS)

