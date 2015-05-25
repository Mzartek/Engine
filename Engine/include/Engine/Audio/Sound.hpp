#ifndef SOUND_HEADER
#define SOUND_HEADER

#include "../Object.hpp"

namespace Engine
{
	namespace Audio
	{
		class DLLAPI Sound : public Object
		{
		private:
			ALuint _source;
			ALuint _buffer;

		public:
			Sound(void);
			~Sound(void);
			void loadFromFile(const ALchar *file, ALsizei frequency, ALenum format);
			void setGain(ALfloat gain);
			void setPitch(ALfloat pitch);
			void setLoop(ALboolean loop);
			void setPosition(const glm::vec3 &pos);
			void setVelocity(const glm::vec3 &vel);
			void setDistances(ALfloat min_dist, ALfloat max_dist, ALfloat rolloff = 1.0f, ALfloat min_gain = 0.0f, ALfloat max_gain = 1.0f);
			ALint getState(void);
			void play(void);
			void pause(void);
			void stop(void);
		};
	}
}

#endif