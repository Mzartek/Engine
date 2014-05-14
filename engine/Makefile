# Makefile for making dll
CC= g++
LIBNAME= Engine
DIR= lib/
SYSTEM= $(shell uname)
ifeq ($(SYSTEM), Linux)
LIB= -Iinclude -fPIC -lGL -lSDL2 -lSDL2_image -lSDL2_mixer -lm
else
BIN= bin/
LIB= -DWIN32 -DENGINE_EXPORTS -Iinclude -I/c/MinGW/tiers/include -L/c/MinGW/tiers/lib -lopengl32 -lglew32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lm
endif
FLAGS= -O3 -W -Wall -Wextra -Werror -Wfatal-errors $(LIB)
SRC= matrix.cpp textureLoader.cpp Object.cpp Window.cpp Camera.cpp MovableCamera.cpp FreeCam.cpp PlayerCam.cpp ShaderProgram.cpp Renderer.cpp Model.cpp OBJModel.cpp Light.cpp DirLight.cpp SpotLight.cpp ShadowMap.cpp SkyBox.cpp Screen.cpp
OBJ= $(SRC:%.cpp=obj/%.o)
IMPORT= -Wl,--out-implib,$(DIR)lib$(LIBNAME).a

all:	$(OBJ)
ifeq ($(SYSTEM), Linux)
	$(CC) -shared -o $(DIR)lib$(LIBNAME).so $^ $(FLAGS)
else
	$(CC) -shared -o $(BIN)$(LIBNAME).dll $^ $(FLAGS) $(IMPORT)
endif

obj/%.o:	%.cpp
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f include/Engine/*~
	rm -f *#
	rm -f $(DIR)lib$(LIBNAME).so
	rm -f $(BIN)$(LIBNAME).dll $(DIR)lib$(LIBNAME).a
