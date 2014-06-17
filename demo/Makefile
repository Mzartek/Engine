# HAVRANEK Kevin
# 12310320
CC= g++
NAME= sample
DIR= bin/
SYSTEM= $(shell uname)
ifeq ($(SYSTEM), Linux)
LIB= -I../engine/include -L../engine/lib -Wl,-rpath=../engine/lib -lSDL2 -lSDL2_mixer
else
LIB= -I../engine/include -L../engine/lib -I/c/MinGW/user/include -L/c/MinGW/user/lib -lmingw32 -lSDL2main -lSDL2
endif
FLAGS= -W -Wall -Wextra -Wfatal-errors -lEngine $(LIB)
SRC= main.cpp config.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

all:	$(OBJ) 
	$(CC) -o $(DIR)$(NAME) $^ $(FLAGS)

obj/%.o:	%.cpp
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f shader/*~
	rm -f *#
	rm -f $(DIR)$(NAME)
	rm -f $(DIR)$(NAME).exe
