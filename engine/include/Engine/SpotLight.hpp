#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "Light.hpp"

namespace engine
{
	class DLLAPI SpotLight : public Light
	{
	protected:
		// Location or Index
		GLfloat _lightSpotCutOff;
		GLint _lightPositionLocation;
		GLint _lightDirectionLocation;
		GLint _lightSpotCutOffLocation;
	public:
		SpotLight(void);
		~SpotLight(void);
		void config(ShaderProgram *program);
		void setSpotCutOff(const float &x);
		GLfloat getSpotCutOff(void) const;
		GLint getLightPositionLocation(void) const;
		GLint getLightDirectionLocation(void) const;
		GLint getLightSpotCutOffLocation(void) const;
		void position(void);
	};
}

#endif
