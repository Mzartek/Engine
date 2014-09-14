#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "Light.hpp"

namespace engine
{
	class DLLAPI SpotLight : public Light
	{
	private:
		struct lightInfo
		{
			glm::vec3 ALIGN(16) color;
			glm::vec3 ALIGN(16) position;
			glm::vec3 ALIGN(16) direction;
			GLfloat spotCutOff;
			GLint ALIGN(16) withShadowMapping;
		} _lightInfo;
	public:
		SpotLight(void);
		~SpotLight(void);
		void config(ShaderProgram *program);
		void setColor(const glm::vec3 &color);
		void setPosition(const glm::vec3 &pos);
		void setDirection(const glm::vec3 &dir);
		void setSpotCutOff(const float &spot);
		glm::vec3 getColor(void) const;
		glm::vec3 getPosition(void) const;
		glm::vec3 getDirection(void) const;
		GLfloat getSpotCutOff(void) const;
		void activateShadowMapping(const GLboolean &shadow);
		void position(void);
		void display(GBuffer *gbuf, Camera *cam);
	};
}

#endif
