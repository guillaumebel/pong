#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([pong], [0.1], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([src/Pong.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

AM_INIT_AUTOMAKE

# Checks for libraries.
PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.10.0,,
                  AC_MSG_ERROR([GTK+-2.10 is required to compile Pong]))
PKG_CHECK_MODULES(CLUTTER, clutter-0.8 clutter-gtk-0.8 clutter-cairo-0.8 ,,
                  AC_MSG_ERROR([clutter-0.8 is required to compile Pong]))

AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)
AC_SUBST(CLUTTER_CFLAGS)
AC_SUBST(CLUTTER_LIBS)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
