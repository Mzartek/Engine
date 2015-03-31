#ifndef SOUND_HEADER
#define SOUND_HEADER

#include "Object.hpp"

namespace Engine
{
	class DLLAPI Sound : public Object
	{
	private:
		ALuint _source;
		ALuint _buffer;
	public:
		Sound(void);
		~Sound(void);
		void loadFromFile(const ALchar *file, const ALsizei &frequency, const ALenum &format);
		void setGain(const ALfloat &gain);
		void setPitch(const ALfloat &pitch);
		void setLoop(const ALboolean &loop);
		void setPosition(const glm::vec3 &pos);
		void setVelocity(const glm::vec3 &vel);
		void setDistances(const ALfloat &min_dist, const ALfloat &max_dist, const ALfloat &rolloff = 1.0f, const ALfloat &min_gain = 0.0f, const ALfloat &max_gain = 1.0f);
		ALint getState(void);
		void play(void);
		void pause(void);
		void stop(void);
	};
}

#endif