#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([X4], [0.0.1], [evilnet-devel@lists.sourceforge.net])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-ldl':
AC_CHECK_LIB([dl], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK

dnl Now check for --enable-pedantic
AC_MSG_CHECKING([whether to enable pedantic compiler warnings])
AC_ARG_ENABLE([pedantic],
[  --enable-pedantic       Enable pedantic warnings (add -pedantic to CFLAGS)],
[x4conf_cv_enable_pedantic=$enable_pedantic],
[AC_CACHE_VAL(x4conf_cv_enable_pedantic,
[x4conf_cv_enable_pedantic=no])])
AC_MSG_RESULT([$x4conf_cv_enable_pedantic])

if test x"$x4conf_cv_enable_pedantic" = xyes; then
    CFLAGS="-pedantic $CFLAGS"
fi

dnl Now check for --enable-warnings
AC_MSG_CHECKING([whether to enable compiler warnings])
AC_ARG_ENABLE([warnings],
[  --enable-warnings       Enable warnings (add -Wall to CFLAGS)],
[x4conf_cv_enable_warnings=$enable_warnings],
[AC_CACHE_VAL(x4conf_cv_enable_warnings,
[x4conf_cv_enable_warnings=no])])
AC_MSG_RESULT([$x4conf_cv_enable_warnings])

if test x"$x4conf_cv_enable_warnings" = xyes; then
    CFLAGS="-Wall $CFLAGS"
fi

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
