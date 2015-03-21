AC_INIT([Engine-GL4-], [1.0])
AM_INIT_AUTOMAKE([subdir-objects -Wall])

AC_LANG(C++)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AM_PROG_AR

LT_INIT

CXXFLAGS="-std=c++11 -Wall -O3"
LIBFLAGS="-lSDL2 -lSDL2_image -lSDL2_ttf -lassimp"

AC_CANONICAL_HOST
case $host_os in
    linux*)
        # Linux system
        LIBFLAGS="-lGL $LIBFLAGS"
        ;;
    *mingw32)
        # MinGW32 system
        LDFLAGS="-lmingw32"
        LIBFLAGS="-lopengl32 -lglew32 -lSDL2main $LIBFLAGS"
        ;;
    *)
        AC_MSG_ERROR([Your platform is not currently supported ($host_os)])
        ;;
esac

AC_SUBST(LIBFLAGS)

AC_CONFIG_FILES([Makefile Engine/Makefile Demo/Makefile])
AC_OUTPUT
