AC_INIT(Engine-GL4-, 1.0)
AM_INIT_AUTOMAKE(subdir-objects -Wall)

AC_LANG(C++)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AM_PROG_AR

LT_INIT

CPPFLAGS="-std=c++11 -Wall"
LDFLAGS=""

AC_CANONICAL_HOST
case $host_os in
    linux*)
        # Linux system
	AC_CHECK_LIB(GL, main, [], AC_MSG_ERROR(OpenGL lib not found))
	AC_CHECK_HEADER(GL/gl.h, [], AC_MSG_ERROR(OpenGL headers not found))

	AC_CHECK_LIB(openal, main, [], AC_MSG_ERROR(OpenAL lib not found))
	AC_CHECK_HEADER(AL/al.h, [], AC_MSG_ERROR(OpenAL headers not found))
        ;;
    *mingw32)
        # MinGW32 system
	AC_CHECK_LIB(mingw32, main, [], AC_MSG_ERROR(MinGW32 lib not found))

	AC_CHECK_LIB(glew32, main, [], AC_MSG_ERROR(GLEW lib not found))
	AC_CHECK_HEADER(GL/glew.h, [], AC_MSG_ERROR(GLEW headers not found))

	AC_CHECK_LIB(opengl32, main, [], AC_MSG_ERROR(OpenGL lib not found))
	AC_CHECK_HEADER(GL/gl.h, [], AC_MSG_ERROR(OpenGL headers not found))

	AC_CHECK_LIB(OpenAL32, main, [], AC_MSG_ERROR(OpenAL lib not found))
	AC_CHECK_HEADER(AL/al.h, [], AC_MSG_ERROR(OpenAL headers not found))
        ;;
    *)
        AC_MSG_ERROR(Your platform is not currently supported ($host_os))
        ;;
esac

AC_CHECK_HEADER(glm/glm.hpp, [], AC_MSG_ERROR(GLM headers not found))

AC_CHECK_LIB(SDL2, main, [], AC_MSG_ERROR(SDL2 lib not found))
AC_CHECK_HEADER(SDL2/SDL.h, [], AC_MSG_ERROR(SDL2 headers not found))

AC_CHECK_LIB(SDL2_image, main, [], AC_MSG_ERROR(SDL2_image lib not found))
AC_CHECK_HEADER(SDL2/SDL_image.h, [], AC_MSG_ERROR(SDL2_image headers not found))

AC_CHECK_LIB(SDL2_ttf, main, [], AC_MSG_ERROR(SDL2_ttf lib not found))
AC_CHECK_HEADER(SDL2/SDL_ttf.h, [], AC_MSG_ERROR(SDL2_ttf headers not found))

AC_CHECK_LIB(SDL2_mixer, main, [], AC_MSG_ERROR(SDL2_mixer lib not found))
AC_CHECK_HEADER(SDL2/SDL_mixer.h, [], AC_MSG_ERROR(SDL2_mixer headers not found))

AC_CHECK_LIB(assimp, main, [], AC_MSG_ERROR(Assimp lib not found))
AC_CHECK_HEADER(assimp/Importer.hpp, [], AC_MSG_ERROR(Assimp headers not found))

AC_CONFIG_FILES(Makefile Engine/Makefile Demo/Makefile)
AC_OUTPUT
