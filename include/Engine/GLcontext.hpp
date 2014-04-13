#ifndef GL_CONTEXT
#define GL_CONTEXT

#include "GL.hpp"
#include "ShaderProgram.hpp"
#include "matrix.h"

namespace engine
{
  class GLcontext
  {
  private:
    ShaderProgram *_program;
  public:
    GLfloat VP[16];
    GLfloat depthVP[16];
    static GLuint width;
    static GLuint height;
    static GLfloat near;
    static GLfloat far;
    
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
    
    GLint textureLocation;
    GLcontext(void);
    ~GLcontext(void);
    static void config(const GLuint &w, const GLuint &h, const GLfloat &n, const GLfloat &f);
    static void clear(void);
    void setShaderProgram(ShaderProgram *program);
    GLuint getProgramId(void);
  };
}


#endif
