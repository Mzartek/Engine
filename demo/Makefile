# HAVRANEK Kevin
# 12310320
CC= g++
NAME= sample
SYSTEM= $(shell uname)
ifeq ($(SYSTEM), Linux)
LIB= -I../include -L../lib -lGL -lSDL2 -lSDL2_image -lSDL2_mixer -lm
else
LIB= -I../include -L../lib -I/c/MinGW/tiers/include -L/c/MinGW/tiers/lib -lopengl32 -lglew32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lm
endif
FLAGS= -O3 -W -Wall -Werror -Wfatal-errors -lEngine $(LIB)
SRC= main.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

all:	$(OBJ) 
	$(CC) -o $(NAME) $^ $(FLAGS)

obj/%.o:	%.cpp
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm -f $(OBJ)
ifeq ($(SYSTEM), Linux)
	rm -f *~
	rm -f *#
	rm -f $(NAME)
else
	rm -f $(NAME).exe
endif
