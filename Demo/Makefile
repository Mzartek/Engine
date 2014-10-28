# Makefile for demo

CC= g++
NAME= Demo
DIR_DEBUG= bin/Debug/
DIR_RELEASE= bin/Release/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS_DEBUG= -std=c++11 -Wall -g -I../Engine/include
COMPILER_OPTIONS_RELEASE= -std=c++11 -Wall -O3 -I../Engine/include
LINKER_OPTIONS_DEBUG= -L../Engine/bin/Debug -lEngine -Wl,-rpath=../Engine/bin/Debug
LINKER_OPTIONS_RELEASE= -L../Engine/bin/Release -lEngine -Wl,-rpath=../Engine/bin/Release

else

COMPILER_OPTIONS_DEBUG= -std=c++11 -Wall -g -I../Engine/include -I/MinGW/user/include -DWIN32 -DGCC
COMPILER_OPTIONS_RELEASE= -std=c++11 -Wall -O3 -I../Engine/include -I/MinGW/user/include -DWIN32 -DGCC
LINKER_OPTIONS_DEBUG= -L../Engine/bin/Debug -L/MinGW/user/lib -lmingw32 -lSDL2main -lSDL2 -lEngine
LINKER_OPTIONS_RELEASE= -L../Engine/bin/Release -L/MinGW/user/lib -lmingw32 -lSDL2main -lSDL2 -lEngine

endif

SRC= src/main.cpp src/config.cpp src/Mushroom.cpp src/Cepe.cpp src/Phalloide.cpp src/Satan.cpp src/Player.cpp
OBJ_DEBUG= $(SRC:%.cpp=obj/Debug/%.o)
OBJ_RELEASE= $(SRC:%.cpp=obj/Release/%.o)

Debug:	$(OBJ_DEBUG)
ifeq ($(SYSTEM), Linux)
	$(CC) $^ -o $(DIR_DEBUG)$(NAME) $(LINKER_OPTIONS_DEBUG)
else
	$(CC) $^ -o $(DIR_DEBUG)$(NAME) $(LINKER_OPTIONS_DEBUG)
endif

Release:	$(OBJ_RELEASE)
ifeq ($(SYSTEM), Linux)
	$(CC) $^ -o $(DIR_RELEASE)$(NAME) $(LINKER_OPTIONS_RELEASE)
else
	$(CC) $^ -o $(DIR_RELEASE)$(NAME) $(LINKER_OPTIONS_RELEASE)
endif

obj/Debug/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS_DEBUG) -c $^ -o $@

obj/Release/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS_RELEASE) -c $^ -o $@

cleanDebug:
	rm -f $(OBJ_DEBUG)
	rm -f *~
	rm -f src/*~
	rm -f $(DIR_DEBUG)$(NAME)
	rm -f $(DIR_DEBUG)$(NAME).exe

cleanRelease:
	rm -f $(OBJ_RELEASE)
	rm -f *~
	rm -f src/*~
	rm -f $(DIR_RELEASE)$(NAME)
	rm -f $(DIR_RELEASE)$(NAME).exe
