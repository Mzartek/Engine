# HAVRANEK Kevin
# 12310320
CC= g++
NAME= test
LIB= -I/c/MinGW/tiers/include -L/c/MinGW/tiers/lib
GLWINDOWS= $(LIB) -lopengl32 -lglu32 -lglew32 -lmingw32 -lSDL2main
GLLINUX= -lGL -lGLU -lGLEW
FLAGS= -O3 -march=native -Wall -Werror -Wfatal-errors -lEngine $(GLLINUX) -lSDL2 -lSDL2_image -lm
SRC= main.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

all:	$(OBJ) 
	$(CC) -o $(NAME) $^ $(FLAGS)

obj/%.o:	%.cpp
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
	rm -f $(NAME)
	rm -f $(NAME).exe
