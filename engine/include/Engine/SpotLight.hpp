#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "Light.hpp"

namespace engine
{
	class DLLAPI SpotLight : public Light
	{
	protected:
		struct lightInfo
		{
			glm::vec3 ALIGN_16 color;
			glm::vec3 ALIGN_16 position;
			glm::vec3 ALIGN_16 direction;
			GLfloat spotCutOff;
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
		void position(void);
		void display(GBuffer *g, Camera *cam);
	};
}

#endif
