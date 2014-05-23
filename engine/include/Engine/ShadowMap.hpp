#ifndef SHADOW_MAP
#define SHADOW_MAP

#include "FrameBuffer.hpp"

namespace engine
{
	class DLLAPI ShadowMap : public FrameBuffer
	{
	public:
		GLint MVPLocation;
		ShadowMap(void);
		~ShadowMap(void);
		void config(const GLuint &width, const GLuint &height, ShaderProgram *program);
	};
}

#endif
