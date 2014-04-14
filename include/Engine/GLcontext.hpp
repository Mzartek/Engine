#ifndef GL_CONTEXT
#define GL_CONTEXT

#include "GL.hpp"
#include "matrix.h"
#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "DirLight.hpp"
#include "SpotLight.hpp"

#define LIGHT0 0

namespace engine
{
  class GLcontext
  {
  private:
    ShaderProgram *_program;
    Camera *_cam;
    DirLight *_dlight0;
    SpotLight *_slight0;
  public:
    GLint MVPLocation;
    GLint modelMatrixLocation;
    GLint normalMatrixLocation;
    
    GLint matAmbientLocation;
    GLint matDiffuseLocation;
    GLint matSpecularLocation;
    GLint matShininessLocation;
    
    GLint camPositionLocation;

    GLint dirLightDirectionLocation0;
    GLint dirLightAmbientLocation0;
    GLint dirLightDiffuseLocation0;
    GLint dirLightSpecularLocation0;
    GLint dirShadowMVPLocation0;
    GLint dirShadowMapLocation0;
    
    GLint spotLightPositionLocation0;
    GLint spotLightDirectionLocation0;
    GLint spotLightSpotCutOffLocation0;
    GLint spotLightAmbientLocation0;
    GLint spotLightDiffuseLocation0;
    GLint spotLightSpecularLocation0;
    GLint spotShadowMVPLocation0;
    GLint spotShadowMapLocation0;
    
    GLint textureLocation;
    GLcontext(void);
    ~GLcontext(void);
    void setShaderProgram(ShaderProgram *program);
    void setCamera(Camera *cam);
    void setDirLight(const GLuint &lightn, DirLight *light);
    void setSpotLight(const GLuint &lightn, SpotLight *light);
    GLuint getProgramId(void);
    Camera *getCamera(void);
    DirLight *getDirLight(const GLuint &lightn);
    SpotLight *getSpotLight(const GLuint &lightn);
    void shadowClear(void);
    void newLoop(void);
  };
}


#endif
