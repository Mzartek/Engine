AM_CPPFLAGS = -I$(top_builddir)/Engine/include
AM_LDFLAGS =

noinst_PROGRAMS = $(top_builddir)/bin/Demo

__top_builddir__bin_Demo_LDADD = $(top_builddir)/lib/libEngine.la

__top_builddir__bin_Demo_SOURCES = \
	src/Tree.cpp \
	src/RainEffect.cpp \
	src/Ground.cpp \
	src/Demo_main.cpp \
	src/MoonLight.cpp \
	src/TextDisplay.cpp \
	src/main.cpp \
	src/ExplosionEffect.cpp \
	src/ScreenDisplay.cpp \
	src/TorchLight.cpp \
	src/ThunderLight.cpp \
	src/AnimModel.cpp \
	src/Demo_init.cpp \
	src/Demo_input.cpp \
	src/Helicopter.cpp \
	src/NightBox.cpp \
	src/SmokeEffect.cpp \
	src/FirefliesEffect.cpp

clean-local:
	rm -f *~
	rm -f src/*~
