#include <Engine/Audio.hpp>

Engine::Audio::Audio(void)
{
	_device = alcOpenDevice(NULL);
	if (!_device)
	{
		std::cerr << "Error init OpenAL device: " << alGetError() << std::endl;
		exit(1);
	}

	_context = alcCreateContext(_device, NULL);
	if (!alcMakeContextCurrent(_context))
	{
		std::cerr << "Error init OpenAL context: " << alGetError() << std::endl;
		exit(1);
	}

	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
}

Engine::Audio::~Audio(void)
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

void Engine::Audio::setListenerPosition(const glm::vec3 &pos, const glm::vec3 &view)
{
	glm::vec3 at = glm::normalize(glm::vec3(view.x, 0.0f, view.z));
	ALfloat listenerOri[] = { at.x, at.y, at.z, 0.0f, 1.0f, 0.0f };

	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
}