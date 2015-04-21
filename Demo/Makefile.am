AM_CPPFLAGS = -I$(top_builddir)/Engine/include
AM_LDFLAGS = -L$(top_builddir)/lib -lEngine

bin_PROGRAMS = $(top_builddir)/bin/Demo

__top_builddir__bin_Demo_SOURCES = \
	src/Demo.hpp \
	src/Ground.hpp \
	src/MoonLight.hpp \
	src/NightBox.hpp \
	src/RainEffect.hpp \
	src/ScreenDisplay.hpp \
	src/SmokeEffect.hpp \
	src/TextDisplay.hpp \
	src/TorchLight.hpp \
	src/Tree.hpp \
	\
	src/Demo.cpp \
	src/Ground.cpp \
	src/MoonLight.cpp \
	src/NightBox.cpp \
	src/RainEffect.cpp \
	src/ScreenDisplay.cpp \
	src/SmokeEffect.cpp \
	src/TextDisplay.cpp \
	src/TorchLight.cpp \
	src/Tree.cpp \
	src/main.cpp

clean-local:
	rm -f src/*~
