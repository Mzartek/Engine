#ifndef LIGHT
#define LIGHT

#include "ShadowMap.hpp"
#include "Camera.hpp"
#include "GBuffer.hpp"
#include "LBuffer.hpp"

namespace engine
{
	class DLLAPI Light
	{
	protected:
		GLuint _idVAO;
		GLuint _idVBO;
		ShadowMap *_shadow;
		GLfloat _lightPosition[3];
		GLfloat _lightDirection[3];
		GLfloat _lightColor[3];
		GLfloat _VP[16];
		ShaderProgram *_program;
		// For LBuffer
		GLint _positionTextureLocation;
		GLint _normalTextureLocation;
		GLint _shadowMapLocation;
		GLint _shadowMatrixLocation;
		GLint _lightTextureLocation;
	    GLint _camPositionLocation;
		GLint _lightColorLocation;
	public:
		Light(void);
		Light(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		virtual ~Light(void);
		virtual void config(ShaderProgram *program) = 0;
		void configShadowMap(const GLuint &width, const GLuint &height, ShaderProgram *shadow);
		void setPosition(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void setDirection(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void setColor(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		GLfloat *getPosition(void);
		GLfloat *getDirection(void);
		GLfloat *getColor(void);
		ShadowMap *getShadowMap(void);
		GLfloat *getMatrix(void);
		GLint getPositionTextureLocation(void) const;
		GLint getNormalTextureLocation(void) const;
		GLint getShadowMapLocation(void) const;
		GLint getShadowMatrixLocation(void) const;
		GLint getLightTextureLocation(void) const;
		GLint getCamPositionLocation(void) const;
		GLint getLightColorLocation(void) const;
		void clear(void) const;
		virtual void position(void) = 0;
		virtual void display(Camera *cam, GBuffer *g, LBuffer *l) = 0;
	};
}

#endif
