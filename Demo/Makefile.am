AM_CPPFLAGS = -I$(top_builddir)/Engine/include
AM_LDFLAGS = -L$(top_builddir)/lib -lEngine

bin_PROGRAMS = $(top_builddir)/bin/Demo

__top_builddir__bin_Demo_SOURCES = \
	src/config.hpp \
	src/Phalloide.hpp \
	src/Mushroom.hpp \
	src/Player.hpp \
	src/Cepe.hpp \
	src/Satan.hpp \
	\
	src/Cepe.cpp \
	src/Mushroom.cpp \
	src/Satan.cpp \
	src/Phalloide.cpp \
	src/config.cpp \
	src/Player.cpp \
	src/main.cpp

clean-local:
	rm -f src/*~
