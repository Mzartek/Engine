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
		glm::vec3 getColor(void) const;
		glm::vec3 getDirection(void) const;
		void position(Camera *cam, const GLfloat &dim);
		void display(GBuffer *gbuf, Camera *cam);
	};
}

#endif
