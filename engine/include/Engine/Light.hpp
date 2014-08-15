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
		glm::vec3 *_lightPosition;
		glm::vec3 *_lightDirection;
		glm::vec3 *_lightColor;
		glm::mat4 *_projectionMatrix;
		glm::mat4 *_VPMatrix;
		ShaderProgram *_program;
		GLint _normalTextureLocation;
		GLint _materialTextureLocation;
		GLint _depthTextureLocation;
		GLint _shadowMapLocation;
		GLint _shadowMatrixLocation;
		GLint _screenLocation;
		GLint _IVPLocation;
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
		ShadowMap *getShadowMap(void);
		glm::vec3 getPosition(void) const;
		glm::vec3 getDirection(void) const;
		glm::vec3 getColor(void) const;
		glm::mat4 getProjectionMatrix(void) const;
		glm::mat4 getVPMatrix(void) const;
		void clear(void) const;
		virtual void position(void) = 0;
		virtual void display(GBuffer *g, Camera *cam) = 0;
	};
}

#endif
