# Makefile for demo

CC= g++
NAME= sample
DIR= bin/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS= -std=c++11 -Wall -O3 -I../engine/include
LINKER_OPTIONS= -L../engine/lib -lEngine -Wl,-rpath=../engine/lib

else

COMPILER_OPTIONS= -std=c++11 -Wall -O3 -I../engine/include -I/c/MinGW/user/include
LINKER_OPTIONS= -L../engine/lib -L/c/MinGW/user/lib -lmingw32 -lSDL2 -lSDL2main -lEngine

endif

SRC= src/main.cpp src/config.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

all:	$(OBJ) 
	$(CC) $^ -o $(DIR)$(NAME) $(LINKER_OPTIONS)

obj/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS) -c $^ -o $@

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f shader/*~
	rm -f *#
	rm -f $(DIR)$(NAME)
	rm -f $(DIR)$(NAME).exe
