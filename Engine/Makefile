# Makefile for library

CC= g++
LIBNAME= Engine
MAJOR=1
MINOR=0.0
DIR= bin/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

CFLAGS= -std=c++11 -Wall -fPIC -g -Iinclude -MMD -MP
LDFLAGS= -lGL -lSDL2 -lSDL2_image -lSDL2_ttf -lassimp -Wl,-soname,lib$(LIBNAME).so.$(MAJOR)

else

CFLAGS= -std=c++11 -Wall -g -Iinclude -I/MinGW/user/include -MMD -MP -DWIN32 -DENGINE_EXPORTS -DGCC
LDFLAGS= -L/MinGW/user/lib -lopengl32 -lglew32 -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp -Wl,--out-implib,$(DIR)lib$(LIBNAME).a

endif

SRC= $(shell find src/ -name \*.cpp -print)
OBJ= $(SRC:%.cpp=obj/%.o)
DEP= $(SRC:%.cpp=obj/%.d)

all:	$(OBJ)
ifeq ($(SYSTEM), Linux)
	$(CC) -shared $^ -o $(DIR)lib$(LIBNAME).so.$(MAJOR).$(MINOR) $(LDFLAGS)
	rm -f $(DIR)lib$(LIBNAME).so $(DIR)lib$(LIBNAME).so.$(MAJOR)
	ln -s lib$(LIBNAME).so.$(MAJOR).$(MINOR) $(DIR)lib$(LIBNAME).so.$(MAJOR)
	ln -s lib$(LIBNAME).so.$(MAJOR).$(MINOR) $(DIR)lib$(LIBNAME).so
else
	$(CC) -shared $^ -o $(DIR)$(LIBNAME).dll $(LDFLAGS)
endif

-include $(DEP)

obj/%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f *~
	rm -f src/*~
	rm -f include/Engine/*~
	rm -f $(DIR)lib$(LIBNAME).so $(DIR)lib$(LIBNAME).so.$(MAJOR) $(DIR)lib$(LIBNAME).so.$(MAJOR).$(MINOR)
	rm -f $(DIR)$(LIBNAME).dll $(DIR)lib$(LIBNAME).a
