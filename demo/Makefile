# HAVRANEK Kevin
# 12310320
CC= g++
NAME= sample
SYSTEM= $(shell uname)
ifeq ($(SYSTEM), Linux)
LIB= -I../engine/include -L../engine/lib -Wl,-rpath=../engine/lib -lSDL2 -lSDL2_mixer
else
LIB= -I../engine/include -L../engine/lib -I/c/MinGW/tiers/include -L/c/MinGW/tiers/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
endif
FLAGS= -W -Wall -Wextra -Wconversion -Werror -Wfatal-errors -lEngine $(LIB)
SRC= main.cpp sequence.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

all:	$(OBJ) 
	$(CC) -o $(NAME) $^ $(FLAGS)

obj/%.o:	%.cpp
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f shader/*~
	rm -f *#
	rm -f $(NAME)
	rm -f $(NAME).exe
