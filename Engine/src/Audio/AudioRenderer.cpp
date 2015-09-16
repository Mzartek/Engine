#include <Engine/Audio/AudioRenderer.hpp>

Engine::Audio::AudioRenderer &Engine::Audio::AudioRenderer::Instance(void)
{
	static AudioRenderer instance;
	return instance;
}

Engine::Audio::AudioRenderer::AudioRenderer(void)
{
	_device = alcOpenDevice(nullptr);
	if (!_device)
	{
		throw std::runtime_error("Error init OpenAL device");
	}

	_context = alcCreateContext(_device, nullptr);
	if (!alcMakeContextCurrent(_context))
	{
		throw std::runtime_error("Error init OpenAL context");
	}

	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
}

Engine::Audio::AudioRenderer::~AudioRenderer(void)
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

void Engine::Audio::AudioRenderer::setListenerPosition(const glm::vec3 &pos, const glm::vec3 &at, const glm::vec3 &up) const
{
	ALfloat listenerOri[] = { at.x, at.y, at.z, up.x, up.y, up.z };

	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
}
