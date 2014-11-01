# Makefile for library

CC= g++
LIBNAME= Engine
DIR= bin/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS= -std=c++11 -Wall -fPIC -g -Iinclude
LINKER_OPTIONS= -lGL -lSDL2 -lSDL2_image -lSDL2_ttf -lassimp

else

COMPILER_OPTIONS= -std=c++11 -Wall -g -Iinclude -I/MinGW/user/include -DWIN32 -DENGINE_EXPORTS -DGCC
LINKER_OPTIONS= -L/MinGW/user/lib -lopengl32 -lglew32 -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp -Wl,--out-implib,$(DIR)lib$(LIBNAME).a

endif

SRC= src/Object.cpp src/Mesh.cpp src/Renderer.cpp src/Camera.cpp src/MovableCamera.cpp src/FreeCam.cpp src/PlayerCam.cpp src/ShaderProgram.cpp src/Model.cpp src/Light.cpp src/DirLight.cpp src/SpotLight.cpp src/FrameBuffer.cpp src/ShadowMap.cpp src/SkyBox.cpp src/Screen.cpp src/TextArray.cpp src/GBuffer.cpp src/Buffer.cpp src/Texture.cpp src/Input.cpp
OBJ= $(SRC:%.cpp=obj/%.o)

Debug:	$(OBJ)
ifeq ($(SYSTEM), Linux)
	$(CC) -shared $^ -o $(DIR)lib$(LIBNAME).so $(LINKER_OPTIONS)
else
	$(CC) -shared $^ -o $(DIR)$(LIBNAME).dll $(LINKER_OPTIONS)
endif

obj/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS) -c $^ -o $@

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f src/*~
	rm -f include/Engine/*~
	rm -f $(DIR)lib$(LIBNAME).so
	rm -f $(DIR)$(LIBNAME).dll $(DIR)lib$(LIBNAME).a
