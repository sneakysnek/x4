# what flags you want to pass to the C compiler & linker
AM_CFLAGS = 
AM_LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = x4
x4_SOURCES = main.c \
	engines.c \
	init.c \
	log.c \
	timers.c

EXTRA_x4_SOURCES = engine_select.c

ENGINE_C = @ENGINE_C@

x4_LDADD = $(ENGINE_C)
x4_DEPENDENCIES = $(ENGINE_C)

nodist_x4_SOURCES = version.c
DISTCLEANFILES = version.c

.PHONY: version.c

version.c: Makefile
	${SHELL} ${srcdir}/version.c.SH ${top_srcdir}
