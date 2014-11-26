# Makefile for demo

CC= g++
NAME= Demo.out
DIR= bin/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

CFLAGS= -std=c++11 -Wall -g -I../Engine/include -MMD -MP
LDFLAGS= -L../Engine/bin/ -lEngine -Wl,-rpath=../Engine/bin/

else

CFLAGS= -std=c++11 -Wall -g -I../Engine/include -I/MinGW/user/include -MMD -MP -DWIN32 -DGCC
LDFLAGS= -L../Engine/bin/ -L/MinGW/user/lib -lmingw32 -lSDL2main -lSDL2 -lEngine

endif

SRC= $(shell find src/ -name \*.cpp -print)
OBJ= $(SRC:%.cpp=obj/%.o)
DEP= $(SRC:%.cpp=obj/%.d)

all:	$(OBJ)
ifeq ($(SYSTEM), Linux)
	$(CC) $^ -o $(DIR)$(NAME) $(LDFLAGS)
else
	$(CC) $^ -o $(DIR)$(NAME) $(LDFLAGS)
endif

-include $(DEP)

obj/%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f *~
	rm -f src/*~
	rm -f $(DIR)$(NAME)
	rm -f $(DIR)$(NAME).exe
