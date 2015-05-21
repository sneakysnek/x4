# what flags you want to pass to the C compiler & linker
AM_CFLAGS = 
AM_LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = x4
x4_SOURCES = main.c \
	init.c \
	init.h \
	log.c  \
	log.h \
	timers.c \
	timers.h \
	version.h

nodist_x4_SOURCES = version.c
DISTCLEANFILES = version.c

.PHONY: version.c

version.c: Makefile
	${SHELL} ${srcdir}/version.c.SH ${top_srcdir}
