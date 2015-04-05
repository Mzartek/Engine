#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#ifdef _WIN32
#ifdef Engine_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#ifdef __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#else
#define ALIGN(X) __declspec(align(X))
#pragma warning(disable:4324)
#pragma warning(disable:4201)
#endif
#include <Windows.h>
#include <GL/glew.h>
#else
#define DLLAPI
#define UNREFERENCED_PARAMETER(P) ((void)P)
#define ALIGN(X) __attribute__((aligned(X)))
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <AL/al.h>
#include <AL/alc.h>

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

namespace Engine
{
	class DLLAPI Object
	{
	private:
		static GLint _memState;
	public:
		Object(void);
		virtual ~Object(void);
		void *operator new(size_t sz);
		void *operator new[](size_t sz);
		void operator delete(void *p);
		void operator delete[](void *p);
		static GLint getMemoryState(void);
		static void saveMemoryInfo(const GLchar *filename);
	};
}

#endif
