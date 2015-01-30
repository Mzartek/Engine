cmake_minimum_required(VERSION 2.6)
PROJECT(Engine)

if(UNIX)

  set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
  set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
  
elseif(WIN32)

  if(MINGW)
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
  elseif(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /EHsc")
	set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
  endif()
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  
  find_path(GLEW_INCLUDE_DIR GL/glew.h)
  
  find_library(GLEW_LIBRARY NAMES GLEW libGLEW)

  set(GLEW_INCLUDE_DIRS GLEW_INCLUDE_DIR)

  set(GLEW_LIBRARIES ${GLEW_LIBRARY})
  
endif()

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
set(ASSIMP_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIR})
set(ENGINE_INCLUDE_DIRS Engine/include)

set(SDL2_LIBRARIES ${SDL2_LIBRARY})
set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY})
set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
set(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})

include_directories(
  ${GLEW_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIRS}
  ${ASSIMP_INCLUDE_DIRS}
  ${ENGINE_INCLUDE_DIRS}
  )

# Engine
file(GLOB_RECURSE engine_header_files ${ENGINE_INCLUDE_DIRS}/*)
file(GLOB_RECURSE engine_source_files Engine/src/*)
add_library(Engine SHARED ${engine_header_files} ${engine_source_files})
set_target_properties(Engine
  PROPERTIES
  VERSION 1.0.0
  SOVERSION 1
  )
target_link_libraries(Engine
  ${GLEW_LIBRARIES}
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

# Install
install(TARGETS Engine DESTINATION lib)
install(FILES ${engine_header_files} DESTINATION include/Engine)