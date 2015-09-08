#ifndef SPOTLIGHT_HEADER
#define SPOTLIGHT_HEADER

#include <Engine/Graphics/Buffer/DepthMap.hpp>

#include "Light.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI SpotLight : public Light
		{
			struct
			{
				glm::vec3 ALIGN(16) color;
				glm::vec3 ALIGN(16) position;
				glm::vec3 ALIGN(16) direction;
				GLfloat spotCutOff;
				GLfloat ALIGN(16) maxDistance;
				glm::mat4 ALIGN(16) shadowMatrix;
			} _lightInfo;

			glm::mat4 _projectionMatrix;
			glm::mat4 _viewMatrix;
			glm::mat4 _VPMatrix;

		public:
			SpotLight(const std::shared_ptr<ShaderProgram> &program);
			~SpotLight(void);
			void setColor(const glm::vec3 &color);
			void setPosition(const glm::vec3 &pos);
			void setDirection(const glm::vec3 &dir);
			void setSpotCutOff(GLfloat spot);
			void setMaxDistance(GLfloat maxDistance);
			const glm::mat4 &getProjectionMatrix(void) const;
			const glm::mat4 &getViewMatrix(void) const;
			const glm::mat4 &getVPMatrix(void) const;
			const glm::vec3 &getColor(void) const;
			const glm::vec3 &getPosition(void) const;
			const glm::vec3 &getDirection(void) const;
			GLfloat getSpotCutOff(void) const;
			GLfloat getMaxDistance(void) const;
			void updateData(const std::shared_ptr<DepthMap> &depthMap);
			void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) override;
			void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam, const std::shared_ptr<DepthMap> &depthMap);
		};
	}
}

#endif
