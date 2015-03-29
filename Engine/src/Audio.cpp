#include <Engine/Audio.hpp>

Engine::Audio::Audio(void)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		std::cerr << "Error init SDL_mixer: " << Mix_GetError() << std::endl;
		exit(1);
	}
}

Engine::Audio::~Audio(void)
{
    Mix_CloseAudio();
}
