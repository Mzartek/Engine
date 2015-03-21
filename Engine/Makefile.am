AM_CPPFLAGS = -Iinclude

lib_LTLIBRARIES = $(top_builddir)/lib/libEngine.la

__top_builddir__lib_libEngineincludedir = $(includedir)/Engine-GL4-
__top_builddir__lib_libEngineinclude_HEADERS = $(shell find include/Engine/ -name "*.hpp")
__top_builddir__lib_libEngine_la_SOURCES = $(shell find src/ -name "*.cpp")

if USE_VERSION_RC
__top_builddir__lib_libEngine_la_LDFLAGS = \
	-no-undefined \
	-release $(LT_RELEASE) \
	-version-info $(VERSION_INFO) -Wl,version.o
__top_builddir__lib_libEngine_la_DEPENDENCIES = version.o
else
__top_builddir__lib_libEngine_la_LDFLAGS = \
	-no-undefined \
	-release 0.1 \
	-version-info $(VERSION_INFO)
endif 

clean-local:
	rm -f include/Engine/*~ src/*~
