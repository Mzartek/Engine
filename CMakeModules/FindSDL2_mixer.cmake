find_library(SDL2_MIXER_LIBRARY NAMES SDL2_mixer libSDL2_mixer)
find_path(SDL2_MIXER_INCLUDE_DIR SDL2/SDL_mixer.h)
set(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_LIBRARY})
set(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_mixer REQUIRED_VARS
	SDL2_MIXER_LIBRARIES
	SDL2_MIXER_INCLUDE_DIRS)
	
mark_as_advanced(SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR)