#ifndef DIRLIGHT_HEADER
#define DIRLIGHT_HEADER

#include "Light.hpp"

#define CSM_NUM 3

namespace Engine
{
	class DLLAPI DirLight : public Light
	{
	private:
		struct
		{
			glm::mat4 shadowMatrix[CSM_NUM];
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
		ShadowMap *getShadowMap(const GLuint &num) const;
		glm::mat4 getProjectionMatrix(const GLuint &num) const;
		glm::mat4 getViewMatrix(const GLuint &num) const;
		glm::mat4 getVPMatrix(const GLuint &num) const;
		glm::vec3 getColor(void) const;
		glm::vec3 getDirection(void) const;
		void position(const glm::vec3 &pos, const GLfloat &dim0, const GLfloat &dim1, const GLfloat &dim2) const;
		void clear(void) const;
		void display(GBuffer *gbuf, Camera *cam);
	};
}

#endif
