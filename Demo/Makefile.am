AM_CPPFLAGS = -I$(top_builddir)/Engine/include
AM_LDFLAGS = -L$(top_builddir)/lib -lEngine

bin_PROGRAMS = $(top_builddir)/bin/Demo

__top_builddir__bin_Demo_SOURCES = \
	src/Demo.hpp \
	src/RainEffect.hpp \
	\
	src/Demo.cpp \
	src/RainEffect.cpp \
	src/main.cpp

clean-local:
	rm -f src/*~
