#ifndef RENDERER
#define RENDERER

#include "GLHead.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "DirLight.hpp"
#include "SpotLight.hpp"

namespace engine
{
	class DLLAPI Renderer
	{
	private:
		ShaderProgram *_program;
		Camera *_cam;
		DirLight *_dlight;
		SpotLight *_slight;
	public:
		GLint MVPLocation;
		GLint modelMatrixLocation;
		GLint normalMatrixLocation;
    
		GLint matAmbientLocation;
		GLint matDiffuseLocation;
		GLint matSpecularLocation;
		GLint matShininessLocation;
    
		GLint camPositionLocation;

		GLint dirLightDirectionLocation;
		GLint dirLightAmbientLocation;
		GLint dirLightDiffuseLocation;
		GLint dirLightSpecularLocation;
		GLint dirShadowMVPLocation;
		GLint dirShadowMapLocation;
    
		GLint spotLightPositionLocation;
		GLint spotLightDirectionLocation;
		GLint spotLightSpotCutOffLocation;
		GLint spotLightAmbientLocation;
		GLint spotLightDiffuseLocation;
		GLint spotLightSpecularLocation;
		GLint spotShadowMVPLocation;
		GLint spotShadowMapLocation;
    
		GLint textureLocation;
    
		Renderer(void);
		~Renderer(void);
		void setShaderProgram(ShaderProgram *program);
		void setCamera(Camera *cam);
		void setDirLight(DirLight *light);
		void setSpotLight(SpotLight *light);
		GLuint getProgramId(void);
		Camera *getCamera(void);
		DirLight *getDirLight(void) const;
		SpotLight *getSpotLight(void) const;
		void newLoop(void);
	};
}


#endif
