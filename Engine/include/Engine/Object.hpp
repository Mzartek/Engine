#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#ifdef _WIN32
#	ifdef Engine_EXPORTS
#		define DLLAPI __declspec(dllexport)
#	else
#		define DLLAPI __declspec(dllimport)
#	endif
#	ifdef __GNUC__
#		define ALIGN(X) __attribute__((aligned(X)))
#	else
#		define ALIGN(X) __declspec(align(X))
#		pragma warning(disable:4324)
#		pragma warning(disable:4201)
#		pragma warning(disable:4251)
#	endif
#	include <Windows.h>
#	include <GL/glew.h>
#else
#	define DLLAPI
#	define UNREFERENCED_PARAMETER(P) ((void)P)
#	define ALIGN(X) __attribute__((aligned(X)))
#	define GL_GLEXT_PROTOTYPES
#	include <GL/gl.h>
#endif

#include <AL/alc.h>
#include <AL/al.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include <array>

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
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#define BUFFER_OFFSET(i) (static_cast<char *>(nullptr) + (i))

namespace Engine
{
	class DLLAPI Object
	{
	public:
		Object(void);
		virtual ~Object(void);
	};
}

#endif
