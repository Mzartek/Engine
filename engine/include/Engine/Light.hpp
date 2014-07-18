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
		ShadowMap *_shadow;
		GLfloat _lightPosition[3];
		GLfloat _lightDirection[3];
		GLfloat _lightColor[3];
		GLfloat _projection[16];
		GLfloat _VPMatrix[16];
		ShaderProgram *_program;
		// For LBuffer
		GLint _normalTextureLocation;
		GLint _materialTextureLocation;
		GLint _depthTextureLocation;
		GLint _shadowMapLocation;
		GLint _shadowMatrixLocation;
		GLint _screenLocation;
		GLint _IVPLocation;
		GLint _lightTextureLocation;
	    GLint _camPositionLocation;
		GLint _lightColorLocation;
		GLint _lightDirectionLocation;
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
		GLfloat *getVPMatrix(void);
		void clear(void) const;
		virtual void position(void) = 0;
		virtual void display(GBuffer *g, Camera *cam) = 0;
	};
}

#endif
