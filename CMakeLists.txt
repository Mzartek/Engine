cmake_minimum_required(VERSION 2.6)
PROJECT(Engine)

# c++11
set(CMAKE_CXX_FLAGS "-std=c++0x")

# Ouput Directories
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# External dep
find_package(OpenGL)

find_path(GLM_INCLUDE_DIR glm/glm.hpp)
find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)
find_path(ASSIMP_INCLUDE_DIR assimp/Importer.hpp)

find_library(SDL2_LIBRARY NAMES SDL2 libSDL2)
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image libSDL2_image)
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf libSDL2_ttf)
find_library(ASSIMP_LIBRARY assimp libassimp)

set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
set(SDL2_LIBRARIES ${SDL2_LIBRARY})
set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY})
set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
set(ASSIMP_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIR})
set(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})

include_directories(Engine/include
  ${OPENGL_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIRS}
  ${ASSIMP_INCLUDE_DIRS}
  )

# Engine
file(GLOB_RECURSE engine_source_files Engine/src/* Engine/include/*)
add_library(Engine SHARED ${engine_source_files})
target_link_libraries(Engine
  ${OPENGL_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${ASSIMP_LIBRARIES}
  )

# Demo
file(GLOB_RECURSE demo_source_files Demo/src/*)
add_executable(Demo ${demo_source_files})
target_link_libraries(Demo Engine)