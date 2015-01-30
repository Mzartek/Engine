cmake_minimum_required(VERSION 2.6)
PROJECT(Engine)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_BINARY_DIR}/CMakeModules")

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Assimp REQUIRED)

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
  
  find_package(GLEW REQUIRED)
  
endif()

set(ENGINE_INCLUDE_DIRS Engine/include)
include_directories(
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
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
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
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