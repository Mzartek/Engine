#ifndef LIGHT
#define LIGHT

#include "ShadowMap.hpp"
#include "Camera.hpp"
#include "GBuffer.hpp"

namespace engine
{
	class DLLAPI Light : public Object
	{
	protected:
		GLuint _idVAO;
		GLuint _idVBO;
		GLuint _idLightInfoBuffer;
		glm::mat4 *_VPMatrix;
		ShadowMap *_shadow;
		// Do not delete it
		ShaderProgram *_program;
		// From GBuffer
		GLint _normalTextureLocation;
		GLint _materialTextureLocation;
		GLint _depthTextureLocation;
		// ShadowMap
		GLint _shadowMapLocation;
		// Matrix
		GLint _shadowMatrixLocation;
		GLint _IVPMatrixLocation;
		// Screen Info
		GLint _screenLocation;
		// Cam Info
		GLint _camPositionLocation;
		// Light Info
		GLuint _lightInfoBlockIndex;
	public:
		Light(void);
		~Light(void);
		void configShadowMap(const GLuint &width, const GLuint &height);
		glm::mat4 getVPMatrix(void) const;
		ShadowMap *getShadowMap(void);
		void clear(void) const;
		virtual void display(GBuffer *gbuf, Camera *cam) = 0;
	};
}

#endif
