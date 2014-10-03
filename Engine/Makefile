# Makefile for library

CC= g++
LIBNAME= Engine
DIR_DEBUG= bin/Debug/
DIR_RELEASE= bin/Release/
SYSTEM= $(shell uname)

ifeq ($(SYSTEM), Linux)

COMPILER_OPTIONS_DEBUG= -std=c++11 -Wall -fPIC -g -Iinclude
COMPILER_OPTIONS_RELEASE= -std=c++11 -Wall -fPIC -O3 -Iinclude
LINKER_OPTIONS_DEBUG= -lGL -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp
LINKER_OPTIONS_RELEASE= -lGL -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp

else

COMPILER_OPTIONS_DEBUG= -std=c++11 -Wall -g -Iinclude -I/MinGW/user/include -DWIN32 -DENGINE_EXPORTS -DGCC
COMPILER_OPTIONS_RELEASE= -std=c++11 -Wall -O3 -Iinclude -I/MinGW/user/include -DWIN32 -DENGINE_EXPORTS -DGCC
LINKER_OPTIONS_DEBUG= -L/MinGW/user/lib -lopengl32 -lglew32 -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp -Wl,--out-implib,$(DIR_DEBUG)lib$(LIBNAME).a
LINKER_OPTIONS_RELEASE= -L/MinGW/user/lib -lopengl32 -lglew32 -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lassimp -Wl,--out-implib,$(DIR_RELEASE)lib$(LIBNAME).a

endif

SRC= src/Object.cpp src/Mesh.cpp src/Renderer.cpp src/Camera.cpp src/MovableCamera.cpp src/FreeCam.cpp src/PlayerCam.cpp src/ShaderProgram.cpp src/Model.cpp src/Light.cpp src/DirLight.cpp src/SpotLight.cpp src/FrameBuffer.cpp src/ShadowMap.cpp src/SkyBox.cpp src/Screen.cpp src/TextArray.cpp src/GBuffer.cpp src/Buffer.cpp src/Texture.cpp src/Input.cpp
OBJ_DEBUG= $(SRC:%.cpp=obj/Debug/%.o)
OBJ_RELEASE= $(SRC:%.cpp=obj/Release/%.o)

Debug:	$(OBJ_DEBUG)
ifeq ($(SYSTEM), Linux)
	$(CC) -shared $^ -o $(DIR_DEBUG)lib$(LIBNAME).so $(LINKER_OPTIONS_DEBUG)
else
	$(CC) -shared $^ -o $(DIR_DEBUG)$(LIBNAME).dll $(LINKER_OPTIONS_DEBUG)
endif

Release:	$(OBJ_RELEASE)
ifeq ($(SYSTEM), Linux)
	$(CC) -shared $^ -o $(DIR_RELEASE)lib$(LIBNAME).so $(LINKER_OPTIONS_RELEASE)
else
	$(CC) -shared $^ -o $(DIR_RELEASE)$(LIBNAME).dll $(LINKER_OPTIONS_RELEASE)
endif

obj/Debug/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS_DEBUG) -c $^ -o $@

obj/Release/%.o:	%.cpp
	$(CC) $(COMPILER_OPTIONS_RELEASE) -c $^ -o $@

cleanDebug:
	rm -f $(OBJ_DEBUG)
	rm -f *~
	rm -f src/*~
	rm -f include/Engine/*~
	rm -f $(DIR_DEBUG)lib$(LIBNAME).so
	rm -f $(DIR_DEBUG)$(LIBNAME).dll $(DIR_DEBUG)lib$(LIBNAME).a

cleanRelease:
	rm -f $(OBJ_RELEASE)
	rm -f *~
	rm -f src/*~
	rm -f include/Engine/*~
	rm -f $(DIR_RELEASE)lib$(LIBNAME).so
	rm -f $(DIR_RELEASE)$(LIBNAME).dll $(DIR_RELEASE)lib$(LIBNAME).a
