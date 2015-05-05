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
			glm::vec3 ALIGN(16) color;
			glm::vec3 ALIGN(16) direction;
			glm::mat4 ALIGN(16) shadowMatrix[CSM_NUM];
		} _lightInfo;
	public:
		DirLight(ShaderProgram *program);
		~DirLight(void);
		void setColor(const glm::vec3 &color);
		void setDirection(const glm::vec3 &dir);
		glm::mat4 getProjectionMatrix(const GLuint &num) const;
		glm::mat4 getViewMatrix(const GLuint &num) const;
		glm::mat4 getVPMatrix(const GLuint &num) const;
		glm::vec3 getColor(void) const;
		glm::vec3 getDirection(void) const;
		void position(const glm::vec3 &pos, const GLfloat &dim0, const GLfloat &dim1, const GLfloat &dim2);
		void display(const GBuffer &gbuf, const PerspCamera &cam);
		void display(const GBuffer &gbuf, const std::array<std::shared_ptr<Engine::DepthMap>, CSM_NUM> &array_depthMap, const PerspCamera &cam);
	};
}

#endif
