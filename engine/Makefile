# Makefile for making dll

CC= g++
LIBNAME= Engine
BIN= bin/
DIR= lib/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS= -std=c++11 -Wall -fPIC -O3 -Iinclude
LINKER_OPTIONS= -lGL -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp

else

COMPILER_OPTIONS= -std=c++11 -Wall -O3 -Iinclude -I/c/MinGW/user/include -DWIN32 -DENGINE_EXPORTS
LINKER_OPTIONS= -L/c/MinGW/user/lib -lopengl32 -lglew32 -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp -Wl,--out-implib,$(DIR)lib$(LIBNAME).a

endif

SRC= textureLoader.cpp Object.cpp GLObject.cpp Renderer.cpp Camera.cpp MovableCamera.cpp FreeCam.cpp PlayerCam.cpp ShaderProgram.cpp Model.cpp Light.cpp DirLight.cpp SpotLight.cpp FrameBuffer.cpp ShadowMap.cpp SkyBox.cpp Screen.cpp TextArray.cpp GBuffer.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

all:	$(OBJ)
ifeq ($(SYSTEM), Linux)
	$(CC) -shared $^ -o $(DIR)lib$(LIBNAME).so $(LINKER_OPTIONS)
else
	$(CC) -shared $^ -o $(BIN)$(LIBNAME).dll $(LINKER_OPTIONS)
endif

obj/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS) -c $^ -o $@

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f include/Engine/*~
	rm -f *#
	rm -f $(DIR)lib$(LIBNAME).so
	rm -f $(BIN)$(LIBNAME).dll $(DIR)lib$(LIBNAME).a
