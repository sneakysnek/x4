#! /bin/sh

echo "Extracting ircd/version.c ..."

srcdir=$1

if test -r version.c
then
   generation=`sed -n 's/^const char \*generation = \"\(.*\)\";/\1/p' < version.c`
   if test ! "$generation" ; then generation=0; fi
else
   generation=0
fi

generation=`expr $generation + 1`

creation=`date | \
awk '{if (NF == 6) \
         { print $1 " " $2 " " $3 " " $6 " at " $4 " " $5 } \
else \
         { print $1 " " $2 " " $3 " " $7 " at " $4 " " $5 " " $6 }}'`

if test -f .release
then
        vcs_version=`cat .release`
else
        vcs_version=`git describe --dirty --long --always`
fi

/bin/cat >version.c <<!SUB!THIS!
#include "version.h"
#include "config.h"

const char *generation = "$generation";
const char *vcs_version = "$vcs_version";
const char *creation = "$creation";
const char *version = PACKAGE_VERSION;
const char *app_version = PACKAGE_NAME " " PACKAGE_VERSION;
!SUB!THIS!
