# Makefile for demo

CC= g++
NAME= Demo
DIR= bin/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS= -std=c++11 -Wall -g -I../Engine/include
LINKER_OPTIONS= -L../Engine/bin/ -lEngine -Wl,-rpath=../Engine/bin/

else

COMPILER_OPTIONS= -std=c++11 -Wall -g -I../Engine/include -I/MinGW/user/include -DWIN32 -DGCC
LINKER_OPTIONS= -L../Engine/bin/ -L/MinGW/user/lib -lmingw32 -lSDL2main -lSDL2 -lEngine

endif

SRC= src/main.cpp src/config.cpp src/Mushroom.cpp src/Cepe.cpp src/Phalloide.cpp src/Satan.cpp src/Player.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

Debug:	$(OBJ)
ifeq ($(SYSTEM), Linux)
	$(CC) $^ -o $(DIR)$(NAME) $(LINKER_OPTIONS)
else
	$(CC) $^ -o $(DIR)$(NAME) $(LINKER_OPTIONS)
endif

obj/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS) -c $^ -o $@

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f src/*~
	rm -f $(DIR)$(NAME)
	rm -f $(DIR)$(NAME).exe
