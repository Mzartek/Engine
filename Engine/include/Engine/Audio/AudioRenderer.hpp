#ifndef AUDIORENDERER_HEADER
#define AUDIORENDERER_HEADER

#include "../Object.hpp"

namespace Engine
{
	namespace Audio
	{
		class DLLAPI AudioRenderer
		{
			ALCdevice *_device;
			ALCcontext *_context;

		public:
			static AudioRenderer &Instance(void);

		private:
			AudioRenderer(void);
			~AudioRenderer(void);

		public:
			void setListenerPosition(const glm::vec3 &pos, const glm::vec3 &at, const glm::vec3 &up) const;
		};
	}
}

#endif
