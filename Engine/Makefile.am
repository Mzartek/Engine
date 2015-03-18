AM_CPPFLAGS = -Iinclude

lib__LTLIBRARIES = $(top_builddir)/lib/Engine.la

Engine_HEADERs = find include/Engine/ -name *.hpp
Engine_SOURCES = find src/ -name *.cpp

if USE_VERSION_RC
lib_LDFLAGS = \
	-no-undefined \
	-release $(LT_RELEASE) \
	-version-info $(VERSION_INFO) -Wl,version.o
lib_DEPENDENCIES = version.o
else
lib_LDFLAGS = \
	-no-undefined \
	-release 0.1 \
	-version-info $(VERSION_INFO)
endif 

clean-local:
	rm -f include/Engine/*~ src/*~
