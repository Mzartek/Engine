# HAVRANEK Kevin
# 12310320
CC= g++
NAME= sample
SYSTEM= $(shell uname)
ifeq ($(SYSTEM), Linux)
LIB= -lGL -lGLU -lGLEW -lSDL2 -lSDL2_image -lm
else
LIB= -I../include -L../lib -I/c/MinGW/tiers/include -L/c/MinGW/tiers/lib -lopengl32 -lglu32 -lglew32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lm
endif
FLAGS= -Wall -Werror -Wfatal-errors -lEngine $(LIB)
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
