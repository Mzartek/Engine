cmake_minimum_required(VERSION 2.6)
PROJECT(KetrazmEngine)

include(${CMAKE_SOURCE_DIR}/CMakeModules/source_group_by_dir.cmake)

set(ENGINE_MAJOR_VERSION 1)
set(ENGINE_MINOR_VERSION 0)
set(ENGINE_MICRO_VERSION 0)
set(ENGINE_VERSION
  ${ENGINE_MAJOR_VERSION}.${ENGINE_MINOR_VERSION}.${ENGINE_MICRO_VERSION})

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

set(OUT_DIR ${CMAKE_SOURCE_DIR}/out)

set(DEMO_SRC_DIR ${CMAKE_SOURCE_DIR}/Demo/src)

set(ENGINE_SRC_DIR ${CMAKE_SOURCE_DIR}/Engine/src)
set(ENGINE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Engine/include)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/CMakeModules")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}/bin)

if(UNIX OR APPLE)

  set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
  
elseif(WIN32)

  if(MINGW)
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
  elseif(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /EHsc")
  endif()
  
  find_package(GLEW REQUIRED)
  
endif()

find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(Assimp REQUIRED)

include_directories(${ENGINE_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${OPENAL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${SDL2_MIXER_INCLUDE_DIRS}
  ${ASSIMP_INCLUDE_DIRS}
  )

# Engine
file(GLOB_RECURSE	engine_source_files ${ENGINE_INCLUDE_DIRS}/*.hpp ${ENGINE_SRC_DIR}/*.hpp ${ENGINE_SRC_DIR}/*.cpp)
add_library(Engine SHARED	${engine_source_files})
source_group_by_dir(engine_source_files)
set_target_properties(Engine
  PROPERTIES
  VERSION ${ENGINE_VERSION}
  SOVERSION ${ENGINE_MAJOR_VERSION}
  )
target_link_libraries(Engine
  ${OPENGL_LIBRARIES}
  ${OPENAL_LIBRARY}
  ${GLEW_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${SDL2_MIXER_LIBRARIES}
  ${ASSIMP_LIBRARIES}
  )

# Demo
file(GLOB_RECURSE demo_source_files ${DEMO_SRC_DIR}/*.hpp ${DEMO_SRC_DIR}/*.cpp)
add_executable(Demo ${demo_source_files})
source_group_by_dir(demo_source_files)
target_link_libraries(Demo Engine)

# Install
install(TARGETS Engine
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(DIRECTORY ${ENGINE_INCLUDE_DIRS}/Engine DESTINATION include)