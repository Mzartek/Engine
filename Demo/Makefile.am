AM_CPPFLAGS = -I$(top_builddir)/Engine/include
AM_LDFLAGS = -L$(top_builddir)/lib -lEngine

bin_PROGRAMS = $(top_builddir)/bin/Demo

__top_builddir__bin_Demo_SOURCES = \
	src/TorchLight.hpp \
	src/SmokeEffect.hpp \
	src/Helicopter.hpp \
	src/Demo.hpp \
	src/ThunderLight.hpp \
	src/Ground.hpp \
	src/RainEffect.hpp \
	src/Tree.hpp \
	src/ScreenDisplay.hpp \
	src/MoonLight.hpp \
	src/AnimModel.hpp \
	src/NightBox.hpp \
	src/ExplosionEffect.hpp \
	src/TextDisplay.hpp \
	\
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
	src/SmokeEffect.cpp

clean-local:
	rm -f *~
	rm -f src/*~
