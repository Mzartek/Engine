#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "Object.hpp"

namespace Engine
{
	class Buffer;
	class ShadowMap;
	class ShaderProgram;
	class GBuffer;
	class Camera;

	class DLLAPI Light : public Object
	{
	protected:
		Buffer *_vertexBuffer;
		Buffer *_mainInfoBuffer;
		Buffer *_lightInfoBuffer;
		ShaderProgram *_program;
		GLuint _idVAO;
		ShadowMap *_shadow;
		glm::mat4 *_projectionMatrix;
		glm::mat4 *_viewMatrix;
		glm::mat4 *_VPMatrix;
	public:
		Light(ShaderProgram *program);
		~Light(void);
		void configShadowMap(const GLuint &width, const GLuint &height);
		glm::mat4 getProjectionMatrix(void) const;
		glm::mat4 getViewMatrix(void) const;
		glm::mat4 getVPMatrix(void) const;
		ShadowMap *getShadowMap(void);
		void clear(void) const;
		virtual void display(GBuffer *gbuf, Camera *cam) = 0;
	};
}

#endif
