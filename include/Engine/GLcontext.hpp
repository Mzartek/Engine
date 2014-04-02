#ifndef GL_CONTEXT
#define GL_CONTEXT

#include "GL.hpp"
#include "ShaderProgram.hpp"
#include "matrix.h"

namespace engine
{
  class GLcontext
  {
    GLfloat _projectionMatrix[16];
    ShaderProgram *_program;
    GLint projectionMatrixLocation;
  public:
    GLint viewMatrixLocation;
    GLint modelMatrixLocation;
    GLint matAmbientLocation;
    GLint matDiffuseLocation;
    GLint matSpecularLocation;
    GLint matShininessLocation;
    GLint camPositionLocation;
    GLint lightPositionLocation;
    GLint lightSpotDirectionLocation;
    GLint lightSpotCutOffLocation;
    GLint lightAmbientLocation;
    GLint lightDiffuseLocation;
    GLint lightSpecularLocation;
    GLint textureLocation;
    GLint shadowTextureLocation;
    GLcontext(void);
    ~GLcontext(void);
    void setShaderProgram(ShaderProgram *program);
    GLuint getProgramId(void);
    void adjust(const int &w, const int &h, const float &fov, const float &near, const float &far);
  };
}


#endif
