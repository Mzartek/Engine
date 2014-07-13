# HAVRANEK Kevin

CC= g++
NAME= sample
DIR= bin/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS= -W -Wall -Wextra -Wfatal-errors -I../engine/include
LINKER_OPTIONS= -L../engine/lib -lEngine -Wl,-rpath=../engine/lib

else

COMPILER_OPTIONS= -W -Wall -Wextra -Wfatal-errors -I../engine/include -I/c/MinGW/user/include
LINKER_OPTIONS= -L../engine/lib -L/c/MinGW/user/lib -lmingw32 -lSDL2main -lSDL2 -lEngine

endif
SRC= main.cpp config.cpp
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
