AM_CPPFLAGS = -I$(top_builddir)/Engine/include
AM_LDFLAGS = -L$(top_builddir)/lib -lEngine

bin_PROGRAMS = $(top_builddir)/bin/Demo

__top_builddir__bin_Demo_SOURCES = find src/ -name "*.cpp"

clean-local:
	rm -f src/*~
