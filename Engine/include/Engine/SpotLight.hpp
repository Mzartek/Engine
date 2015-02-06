#ifndef SPOTLIGHT_HEADER
#define SPOTLIGHT_HEADER

#include "Light.hpp"

namespace Engine
{
	class DLLAPI SpotLight : public Light
	{
	private:
		struct
		{
			glm::mat4 shadowMatrix;
			glm::mat4 IVPMatrix;
			glm::uvec2 ALIGN(16) screen;
			glm::vec3 ALIGN(16) camPosition;
		} _mainInfo;

		struct
		{
			glm::vec3 ALIGN(16) color;
			glm::vec3 ALIGN(16) position;
			glm::vec3 ALIGN(16) direction;
			GLfloat spotCutOff;
			GLfloat ALIGN(16) maxDistance;
			GLint withShadowMapping;
		} _lightInfo;
	public:
		SpotLight(ShaderProgram *program);
		~SpotLight(void);
		void setColor(const glm::vec3 &color);
		void setPosition(const glm::vec3 &pos);
		void setDirection(const glm::vec3 &dir);
		void setSpotCutOff(const GLfloat &spot);
		void setMaxDistance(const GLfloat &maxDistance);
		void setShadowMapping(const GLboolean &shadow);
		void configShadowMap(const GLuint &width, const GLuint &height) const;
		ShadowMap *getShadowMap(void) const;
		glm::mat4 getProjectionMatrix(void) const;
		glm::mat4 getViewMatrix(void) const;
		glm::mat4 getVPMatrix(void) const;
		glm::vec3 getColor(void) const;
		glm::vec3 getPosition(void) const;
		glm::vec3 getDirection(void) const;
		GLfloat getSpotCutOff(void) const;
		GLfloat getMaxDistance(void) const;
		void position(void) const;
		void clear(void) const;
		void display(GBuffer *gbuf, Camera *cam);
	};
}

#endif
