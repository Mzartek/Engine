#ifndef AUDIO_HEADER
#define AUDIO_HEADER

#include "../Object.hpp"

namespace Engine
{
	class DLLAPI Audio
	{
	private:
		Audio(void);
		~Audio(void);

		ALCdevice *_device;
		ALCcontext *_context;

	public:
		static Audio &Instance(void);

		void setListenerPosition(const glm::vec3 &pos, const glm::vec3 &at, const glm::vec3 &up) const;
	};
}

#endif
