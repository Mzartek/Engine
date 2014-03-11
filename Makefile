# Makefile for making dll
CC= g++
LIBNAME= Engine
DIR= lib/
LIBLINUX= -fPIC -lGL -lGLU -lGLEW -lSDL2 -lSDL2_image
LIBWINDOWS= -I/c/MinGW/tiers/include -L/c/MinGW/tiers/lib -lopengl32 -lglu32 -lglew32 -lSDL2 -lSDL2_image
FLAGS= -O3 -Wall -Werror -Wfatal-errors $(LIBLINUX)
SRC= GL.cpp Object.cpp Window.cpp Camera.cpp FreeCam.cpp PlayerCam.cpp ShaderLoader.cpp ShaderProgram.cpp
OBJ= $(SRC:%.cpp=obj/%.o)
IMPORT= -Wl,--out-implib,$(DIR)lib$(LIBNAME).a

all:	
	@echo "make [os]"

win:	$(OBJ) 
	$(CC) -shared -o $(DIR)$(LIBNAME).dll $^ $(FLAGS) $(IMPORT)

linux:	$(OBJ) 
	$(CC) -shared -o $(DIR)lib$(LIBNAME).so $^ $(FLAGS)

obj/%.o:	%.cpp
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
	rm -f $(DIR)lib$(LIBNAME).so
	rm -f $(DIR)$(LIBNAME).dll $(DIR)lib$(LIBNAME).a
