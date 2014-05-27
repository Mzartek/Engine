#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "Light.hpp"

namespace engine
{
	class DLLAPI SpotLight : public Light
	{
	protected:
		GLfloat _lightSpotCutOff[1];
		GLint _lightPositionLocation;
		GLint _lightDirectionLocation;
		GLint _lightSpotCutOffLocation;
	public:
		SpotLight(void);
		~SpotLight(void);
		void config(ShaderProgram *program);
		void setSpotCutOff(const float &x);
		GLfloat *getSpotCutOff(void);
		GLint getLightPositionLocation(void) const;
		GLint getLightDirectionLocation(void) const;
		GLint getLightSpotCutOffLocation(void) const;
		void position(void);
	};
}

#endif
