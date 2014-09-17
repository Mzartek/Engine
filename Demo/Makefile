# Makefile for demo

CC= g++
NAME= Demo
DIR= bin/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS= -std=c++11 -Wall -O3 -I../Engine/include
LINKER_OPTIONS= -L../Engine/bin -lEngine -Wl,-rpath=../Engine/bin

else

COMPILER_OPTIONS= -std=c++11 -Wall -O3 -I../Engine/include -I/c/MinGW/user/include -DWIN32 -DGCC
LINKER_OPTIONS= -L../Engine/lib -L/c/MinGW/user/lib -lmingw32 -lSDL2 -lSDL2main -lEngine

endif

SRC= src/main.cpp src/config.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

all:	$(OBJ) 
ifeq ($(SYSTEM), Linux)
	$(CC) $^ -o $(DIR)$(NAME).out $(LINKER_OPTIONS)
else
	$(CC) $^ -o $(DIR)$(NAME) $(LINKER_OPTIONS)
endif

obj/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS) -c $^ -o $@

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f src/*~
	rm -f $(DIR)$(NAME).out
	rm -f $(DIR)$(NAME).exe
