#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.50])
AC_INIT([pong], [0.1], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

AM_INIT_AUTOMAKE

# Checks for libraries.
CLUTTER_REQUIRED=1.0.0
CLUTTER_GTK_REQUIRED=0.10.2

PKG_CHECK_MODULES([CLUTTER],[
  clutter-1.0 >= $CLUTTER_REQUIRED])
AC_SUBST([CLUTTER_CFLAGS])
AC_SUBST([CLUTTER_LIBS])
 PKG_CHECK_MODULES([CLUTTER_GTK],[
  clutter-gtk-0.10  >= $CLUTTER_GTK_REQUIRED])
AC_SUBST([CLUTTER_GTK_CFLAGS])
AC_SUBST([CLUTTER_GTK_LIBS])

PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.10.0,,
                  AC_MSG_ERROR([GTK+-2.10 is required to compile Pong]))
PKG_CHECK_MODULES(GCONF, gconf-2.0 >= 2.0,,
                  AC_MSG_ERROR([gconf-2.0 is required to compile Pong]))

AC_SUBST(GCONF_CFLAGS)
AC_SUBST(GCONF_LIBS)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
