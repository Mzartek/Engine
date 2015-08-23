#include <Engine/Audio/Sound.hpp>

#define CHUNK_SIZE 4096

Engine::Audio::Sound::Sound(void)
	: _buffer(0)
{
	alGenSources(1, &_source);
}

Engine::Audio::Sound::~Sound(void)
{
	alDeleteSources(1, &_source);
	if (alIsBuffer(_buffer)) alDeleteBuffers(1, &_buffer);
}

void Engine::Audio::Sound::loadFromFile(const ALchar *file, ALsizei frequency, ALenum format)
{
	int state = 0;
	switch (format)
	{
	case AL_FORMAT_MONO8:
		state = Mix_OpenAudio(frequency, AUDIO_S8, 1, CHUNK_SIZE);
		break;
	case AL_FORMAT_MONO16:
		state = Mix_OpenAudio(frequency, AUDIO_S16, 1, CHUNK_SIZE);
		break;
	case AL_FORMAT_STEREO8:
		state = Mix_OpenAudio(frequency, AUDIO_S8, 2, CHUNK_SIZE);
		break;
	case AL_FORMAT_STEREO16:
		state = Mix_OpenAudio(frequency, AUDIO_S16, 2, CHUNK_SIZE);
		break;
	}

	if (state == -1)
	{
		throw std::exception(Mix_GetError());
	}

	Mix_Chunk *sound = Mix_LoadWAV(file);

	if (sound == NULL)
	{
		throw std::exception(std::string("Failed to read the file: " + std::string(file) + Mix_GetError()).c_str());
	}

	if (alIsBuffer(_buffer)) alDeleteBuffers(1, &_buffer);
	alGenBuffers(1, &_buffer);

	alBufferData(_buffer, format, sound->abuf, sound->alen, frequency);

	alSourcei(_source, AL_BUFFER, _buffer);

	Mix_FreeChunk(sound);
	Mix_CloseAudio();
}

void Engine::Audio::Sound::setGain(ALfloat gain)
{
	alSourcef(_source, AL_GAIN, gain);
}

void Engine::Audio::Sound::setPitch(ALfloat pitch)
{
	alSourcef(_source, AL_PITCH, pitch);
}

void Engine::Audio::Sound::setLoop(ALboolean loop)
{
	alSourcei(_source, AL_LOOPING, loop);
}

void Engine::Audio::Sound::setPosition(const glm::vec3 &pos)
{
	alSource3f(_source, AL_POSITION, pos.x, pos.y, pos.z);
}

void Engine::Audio::Sound::setVelocity(const glm::vec3 &vel)
{
	alSource3f(_source, AL_VELOCITY, vel.x, vel.y, vel.z);
}

void Engine::Audio::Sound::setDistances(ALfloat min_dist, ALfloat max_dist, ALfloat rolloff, ALfloat min_gain, ALfloat max_gain)
{
	alSourcef(_source, AL_REFERENCE_DISTANCE, min_dist);
	alSourcef(_source, AL_MAX_DISTANCE, max_dist);
	alSourcef(_source, AL_ROLLOFF_FACTOR, rolloff);
	alSourcef(_source, AL_MIN_GAIN, min_gain);
	alSourcef(_source, AL_MAX_GAIN, max_gain);
}

ALint Engine::Audio::Sound::getState(void)
{
	ALint state;
	alGetSourcei(_source, AL_SOURCE_STATE, &state);
	return state;
}

void Engine::Audio::Sound::play(void)
{
	alSourcePlay(_source);
}

void Engine::Audio::Sound::pause(void)
{
	alSourcePause(_source);
}

void Engine::Audio::Sound::stop(void)
{
	alSourceStop(_source);
}
