#include <Engine/Audio/Audio.hpp>

Engine::Audio &Engine::Audio::Instance(void)
{
	static Audio instance;
	return instance;
}

Engine::Audio::Audio(void)
{
	_device = alcOpenDevice(NULL);
	if (!_device)
	{
		std::cerr << "Error init OpenAL device: " << alGetError() << std::endl;
		abort();
	}

	_context = alcCreateContext(_device, NULL);
	if (!alcMakeContextCurrent(_context))
	{
		std::cerr << "Error init OpenAL context: " << alGetError() << std::endl;
		abort();
	}

	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
}

Engine::Audio::~Audio(void)
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

void Engine::Audio::setListenerPosition(const glm::vec3 &pos, const glm::vec3 &at, const glm::vec3 &up) const
{
	ALfloat listenerOri[] = { at.x, at.y, at.z, up.x, up.y, up.z };

	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
}
