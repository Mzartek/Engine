#ifndef AUDIO_HEADER
#define AUDIO_HEADER

#include "../Object.hpp"

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
		void setListenerPosition(const std::shared_ptr<glm::vec3> &pos, const std::shared_ptr<glm::vec3> &at, const std::shared_ptr<glm::vec3> &up) const;
	};
}

#endif
