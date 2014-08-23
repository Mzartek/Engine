#ifndef DIR_LIGHT
#define DIR_LIGHT

#include "Light.hpp"

namespace engine
{
	class DLLAPI DirLight : public Light
	{
	private:
		struct lightInfo
		{
			glm::vec3 ALIGN_16 color;
			glm::vec3 ALIGN_16 direction;
		} _lightInfo;
	public:
		DirLight(void);
		~DirLight(void);
		void config(ShaderProgram *program);
		void setColor(const glm::vec3 &color);
		void setDirection(const glm::vec3 &dir);
		glm::vec3 getColor(void) const;
		glm::vec3 getDirection(void) const;
		void position(const glm::vec3 &position, const GLfloat &dim);
		void display(GBuffer *g, Camera *cam);
	};
}

#endif
