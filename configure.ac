AC_PREREQ([2.69])
AC_INIT([vector], [1.0.0], [haxpor@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AC_PROG_CC_C_O

AM_PROG_AR

AC_ENABLE_SHARED
AC_ENABLE_STATIC

LT_INIT

# checks for libraries
AC_CHECK_LIB([m], [lroundf])

# checks for header files
AC_CHECK_HEADERS([stdio.h \
                  stdlib.h \
                  string.h \
                  math.h ])

# checks for library functions
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
