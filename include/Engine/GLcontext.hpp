#ifndef GL_CONTEXT
#define GL_CONTEXT

#include "GL.hpp"
#include "ShaderProgram.hpp"
#include "matrix.h"

namespace engine
{
  class GLcontext
  {
    ShaderProgram *_program;
    GLfloat _biasMatrix[16];
  public:
    static GLuint width;
    static GLuint height;
    static GLfloat near;
    static GLfloat far;
    GLint projectionMatrixLocation;
    GLint viewMatrixLocation;
    GLint modelMatrixLocation;
    GLint depthProjectionMatrixLocation;
    GLint depthViewMatrixLocation;
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
    static void config(const GLuint &w, const GLuint &h, const GLfloat &n, const GLfloat &f);
    static void clear(void);
    void setShaderProgram(ShaderProgram *program);
    GLuint getProgramId(void);
  };
}


#endif
