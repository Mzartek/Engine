# Makefile for library

CC= g++
LIBNAME= Engine
BIN= bin/
DIR= lib/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS= -std=c++11 -Wall -fPIC -O3 -Iinclude
LINKER_OPTIONS= -lGL -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp

else

COMPILER_OPTIONS= -std=c++11 -Wall -O3 -Iinclude -I/c/MinGW/user/include -DWIN32 -DENGINE_EXPORTS -DGCC
LINKER_OPTIONS= -L/c/MinGW/user/lib -lopengl32 -lglew32 -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp -Wl,--out-implib,$(DIR)lib$(LIBNAME).a

endif

SRC= src/Object.cpp src/Mesh.cpp src/Renderer.cpp src/Camera.cpp src/MovableCamera.cpp src/FreeCam.cpp src/PlayerCam.cpp src/ShaderProgram.cpp src/Model.cpp src/Light.cpp src/DirLight.cpp src/SpotLight.cpp src/FrameBuffer.cpp src/ShadowMap.cpp src/SkyBox.cpp src/Screen.cpp src/TextArray.cpp src/GBuffer.cpp src/Buffer.cpp src/Texture.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

all:	$(OBJ)
ifeq ($(SYSTEM), Linux)
	$(CC) -shared $^ -o $(BIN)lib$(LIBNAME).so $(LINKER_OPTIONS)
else
	$(CC) -shared $^ -o $(BIN)$(LIBNAME).dll $(LINKER_OPTIONS)
endif

obj/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS) -c $^ -o $@

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f src/*~
	rm -f include/Engine/*~
	rm -f $(BIN)lib$(LIBNAME).so
	rm -f $(BIN)$(LIBNAME).dll $(DIR)lib$(LIBNAME).a
