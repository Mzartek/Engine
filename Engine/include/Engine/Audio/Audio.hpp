#ifndef AUDIO_HEADER
#define AUDIO_HEADER

#include "../Object.hpp"
#include "../Tools/ControllerMemory.hpp"

namespace Engine
{
	class DLLAPI Audio : public Object
	{
	private:
		ALCdevice *_device;
		ALCcontext *_context;
	public:
		Audio(void);
		~Audio(void);
		void setListenerPosition(const glm::vec3 &pos, const glm::vec3 &at, const glm::vec3 &up);
	};
}

#endif
