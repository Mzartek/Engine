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

		std::shared_ptr<std::vector<std::shared_ptr<glm::mat4>>> _projectionMatrix;
		std::shared_ptr<std::vector<std::shared_ptr<glm::mat4>>> _viewMatrix;
		std::shared_ptr<std::vector<std::shared_ptr<glm::mat4>>> _VPMatrix;
	public:
		DirLight(const std::shared_ptr<ShaderProgram> &program);
		~DirLight(void);
		void setColor(const std::shared_ptr<glm::vec3> &color);
		void setDirection(const std::shared_ptr<glm::vec3> &dir);
		const std::shared_ptr<glm::mat4> &getProjectionMatrix(GLuint num) const;
		const std::shared_ptr<glm::mat4> &getViewMatrix(GLuint num) const;
		const std::shared_ptr<glm::mat4> &getVPMatrix(GLuint num) const;
		const std::shared_ptr<glm::vec3> &getColor(void) const;
		const std::shared_ptr<glm::vec3> &getDirection(void) const;
		void position(const std::shared_ptr<glm::vec3> &pos, GLfloat dim0, GLfloat dim1, GLfloat dim2);
		void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam);
		void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam, 
			std::shared_ptr<Engine::DepthMap> &depthMap0, std::shared_ptr<Engine::DepthMap> &depthMap1, std::shared_ptr<Engine::DepthMap> &depthMap2);
	};
}

#endif
