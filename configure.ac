#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([X4], [0.0.1], [evilnet-devel@lists.sourceforge.net])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PREFIX_DEFAULT([$HOME/x4])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-ldl':
AC_CHECK_LIB([dl], [main])

# Checks for header files.
AC_CHECK_HEADERS([assert.h poll.h signal.h stdlib.h stdio.h string.h stdarg.h sys/time.h sys/types.h sys/stat.h time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK

dnl Find out what type of system we are
AC_CANONICAL_HOST

dnl Now look for --enable-debug
AC_MSG_CHECKING([whether to enable debug mode])
AC_ARG_ENABLE([debug],
[  --enable-debug          Turn on debugging mode],
[x4conf_cv_enable_debug=$enable_debug],
[AC_CACHE_VAL(x4conf_cv_enable_debug,
[x4conf_cv_enable_debug=no])])
AC_MSG_RESULT([$x4conf_cv_enable_debug])

if test x"$x4conf_cv_enable_debug" = xyes; then
    AC_DEFINE([DEBUGMODE], 1, [Enable debugging code])
fi

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

dnl Check OS for os_dep files.
AC_MSG_CHECKING(for OS-dependent information)
case "$host" in
    *-linux*)
        AC_MSG_RESULT([Linux ($host) found.])
        x4conf_poll_syscall=yes
        ;;

    *-solaris*)
        AC_MSG_RESULT([Solaris ($host) found.])
        if test x"$ac_cv_header_poll_h" = xyes; then
            x4conf_poll_syscall=yes
        else
            x4conf_poll_syscall=no
        fi
        ;;

    *-sunos*)
        AC_MSG_RESULT([Solaris ($host) found.])
        x4conf_poll_syscall=no
        ;;

    *-openbsd*)
        AC_MSG_RESULT([OpenBSD ($host) found.])
        if test x"$ac_cv_header_poll_h" = xyes; then
            x4conf_poll_syscall=yes
        else
            x4conf_poll_syscall=no
        fi
        ;;

    *-*bsd*)
        AC_MSG_RESULT([Generic BSD ($host) found.])
        if test x"$ac_cv_header_poll_h" = xyes; then
            x4conf_poll_syscall=yes
        else
            x4conf_poll_syscall=no
        fi
        ;;

    *-darwin*)
        AC_MSG_RESULT([Darwin (Mac OS X) ($host) found.])
        x4conf_poll_syscall=no
        ;;

    *)
        AC_MSG_RESULT([Unknown system type $host found.])
        AC_MSG_WARN([Unknown OS type; using generic routines.])
        x4conf_poll_syscall=no
        ;;
esac

ENGINE_C='engine_select.$(OBJEXT)'

dnl Start with --enable-poll
AC_MSG_CHECKING([whether to enable use of poll()])
AC_ARG_ENABLE([poll],
[  --enable-poll           Force poll to be used regardless of whether or not
                          it is a system call],
[x4conf_cv_enable_poll=$enable_poll],
[AC_CACHE_VAL(x4conf_cv_enable_poll,
[x4conf_cv_enable_poll=$x4conf_poll_syscall])])

# Force poll to be disabled if there is no poll.h
if test x"$ac_cv_header_poll_h" != xyes; then
    x4conf_cv_enable_poll=no
fi

AC_MSG_RESULT([$x4conf_cv_enable_poll])

if test x"$x4conf_cv_enable_poll" = xyes; then
    AC_DEFINE([USE_POLL], 1, [Specify whether or not to use poll()])
    ENGINE_POLL='engine_poll.$(OBJEXT)'
    ENGINE_C="$ENGINE_POLL $ENGINE_C"
fi

AC_SUBST([ENGINE_C])

dnl --with-maxcon allows us to set the maximum connections
x4conf_maxcon=`ulimit -Hn`
if test x"$x4conf_maxcon" = xunlimited; then
    x4conf_maxcon=`ulimit -Sn`
fi
x4conf_maxcon=`expr $x4conf_maxcon - 4`
AC_MSG_CHECKING([max connections])
AC_ARG_WITH([maxcon],
[  --with-maxcon=maxcon    Maximum number of connections server will accept],
[x4conf_cv_with_maxcon=$with_maxcon],
[AC_CACHE_VAL(x4conf_cv_with_maxcon,
[x4conf_cv_with_maxcon=$x4conf_maxcon])])

if test x"$x4conf_cv_with_maxcon" = xyes -o x"$x4conf_cv_with_maxcon" = xno; then
    if test "$x4conf_maxcon" -lt 32; then
      AC_MSG_ERROR([Maximum connections (number of open files minus 4) must be at least 32.])
    fi
    x4conf_cv_with_maxcon=$x4conf_maxcon
elif test "$x4conf_cv_with_maxcon" -lt 32; then
    AC_MSG_ERROR([Maximum connections (--with-maxcon) must be at least 32.])
fi

AC_MSG_RESULT([$x4conf_cv_with_maxcon])

AC_DEFINE_UNQUOTED(MAXCONNECTIONS, $x4conf_cv_with_maxcon,
[Maximum number of network connections])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
