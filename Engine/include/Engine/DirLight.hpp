#ifndef DIRLIGHT_HEADER
#define DIRLIGHT_HEADER

#include "Light.hpp"

namespace Engine
{
	class DLLAPI DirLight : public Light
	{
	private:
		struct
		{
			glm::vec3 ALIGN(16) color;
			glm::vec3 ALIGN(16) direction;
			GLint withShadowMapping;
		} _lightInfo;
	public:
		DirLight(ShaderProgram *program);
		~DirLight(void);
		void setColor(const glm::vec3 &color);
		void setDirection(const glm::vec3 &dir);
		void setShadowMapping(const GLboolean &shadow);
		void configShadowMap(const GLuint &width, const GLuint &height) const;
		ShadowMap *getShadowMap(void) const;
		glm::mat4 getProjectionMatrix(void) const;
		glm::mat4 getViewMatrix(void) const;
		glm::mat4 getVPMatrix(void) const;
		glm::vec3 getColor(void) const;
		glm::vec3 getDirection(void) const;
		void position(Camera *cam, const GLfloat &dim) const;
		void clear(void) const;
		void display(GBuffer *gbuf, Camera *cam) const;
	};
}

#endif
