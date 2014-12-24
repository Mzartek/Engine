#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#ifdef WIN32
#ifdef ENGINE_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#ifdef GCC
#define ALIGN(X) __attribute__((aligned(X)))
#else
#define ALIGN(X) __declspec(align(X))
#pragma warning(disable:4324)
#endif
#include <GL/glew.h>
#else
#define DLLAPI
#define ALIGN(X) __attribute__((aligned(X)))
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

#endif
