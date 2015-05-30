m4_define([engine_major_version], [1])
m4_define([engine_minor_version], [0])
m4_define([engine_micro_version], [0])
m4_define([engine_version],
          [engine_major_version.engine_minor_version.engine_micro_version])
	  
AC_INIT(Engine-GL4-, engine_version)
AM_INIT_AUTOMAKE(subdir-objects -Wall)

AC_LANG(C++)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AM_PROG_AR

LT_INIT

CXXFLAGS="-std=c++11 -Wall"
LDFLAGS=

ENGINE_LIBSFLAGS=
ENGINE_MAJOR_VERSION=engine_major_version
ENGINE_MINOR_VERSION=engine_minor_version
ENGINE_MICRO_VERSION=engine_micro_version
ENGINE_VERSION=engine_version

AC_SUBST(ENGINE_LIBSFLAGS)
AC_SUBST(ENGINE_MAJOR_VERSION)
AC_SUBST(ENGINE_MINOR_VERSION)
AC_SUBST(ENGINE_MICRO_VERSION)
AC_SUBST(ENGINE_VERSION)

AC_CANONICAL_HOST
case $host_os in
    linux*)
        # Linux system
	AC_CHECK_LIB(GL, main, ENGINE_LIBSFLAGS="-lGL", AC_MSG_ERROR(OpenGL lib not found))
	AC_CHECK_HEADER(GL/gl.h, [], AC_MSG_ERROR(OpenGL headers not found))

	AC_CHECK_LIB(openal, main, ENGINE_LIBSFLAGS="$ENGINE_LIBSFLAGS -lopenal", AC_MSG_ERROR(OpenAL lib not found))
	AC_CHECK_HEADER(AL/al.h, [], AC_MSG_ERROR(OpenAL headers not found))
        ;;
    *mingw32)
        # MinGW32 system
	AC_CHECK_LIB(mingw32, main, [], AC_MSG_ERROR(MinGW32 lib not found))

	AC_CHECK_LIB(glew32, main, ENGINE_LIBSFLAGS="lglew32", AC_MSG_ERROR(GLEW lib not found))
	AC_CHECK_HEADER(GL/glew.h, [], AC_MSG_ERROR(GLEW headers not found))

	AC_CHECK_LIB(opengl32, main, ENGINE_LIBSFLAGS="$ENGINE_LIBSFLAGS -lopengl32", AC_MSG_ERROR(OpenGL lib not found))
	AC_CHECK_HEADER(GL/gl.h, [], AC_MSG_ERROR(OpenGL headers not found))

	AC_CHECK_LIB(OpenAL32, main, ENGINE_LIBSFLAGS="$ENGINE_LIBSFLAGS -lOpenAL32", AC_MSG_ERROR(OpenAL lib not found))
	AC_CHECK_HEADER(AL/al.h, [], AC_MSG_ERROR(OpenAL headers not found))
        ;;
    *)
        AC_MSG_ERROR(Your platform is not currently supported ($host_os))
        ;;
esac

AC_CHECK_HEADER(glm/glm.hpp, [], AC_MSG_ERROR(GLM headers not found))

AC_CHECK_LIB(SDL2, main, ENGINE_LIBSFLAGS="$ENGINE_LIBSFLAGS -lSDL2", AC_MSG_ERROR(SDL2 lib not found))
AC_CHECK_HEADER(SDL2/SDL.h, [], AC_MSG_ERROR(SDL2 headers not found))

AC_CHECK_LIB(SDL2_image, main, ENGINE_LIBSFLAGS="$ENGINE_LIBSFLAGS -lSDL2_image", AC_MSG_ERROR(SDL2_image lib not found))
AC_CHECK_HEADER(SDL2/SDL_image.h, [], AC_MSG_ERROR(SDL2_image headers not found))

AC_CHECK_LIB(SDL2_ttf, main, ENGINE_LIBSFLAGS="$ENGINE_LIBSFLAGS -lSDL2_ttf", AC_MSG_ERROR(SDL2_ttf lib not found))
AC_CHECK_HEADER(SDL2/SDL_ttf.h, [], AC_MSG_ERROR(SDL2_ttf headers not found))

AC_CHECK_LIB(SDL2_mixer, main, ENGINE_LIBSFLAGS="$ENGINE_LIBSFLAGS -lSDL2_mixer", AC_MSG_ERROR(SDL2_mixer lib not found))
AC_CHECK_HEADER(SDL2/SDL_mixer.h, [], AC_MSG_ERROR(SDL2_mixer headers not found))

AC_CHECK_LIB(assimp, main, ENGINE_LIBSFLAGS="$ENGINE_LIBSFLAGS -lassimp", AC_MSG_ERROR(Assimp lib not found))
AC_CHECK_HEADER(assimp/Importer.hpp, [], AC_MSG_ERROR(Assimp headers not found))

AC_CONFIG_FILES(Makefile Engine/Makefile Demo/Makefile)
AC_OUTPUT
