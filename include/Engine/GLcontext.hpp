#ifndef GL_CONTEXT
#define GL_CONTEXT

#include "GL.hpp"
#include "ShaderProgram.hpp"
#include "matrix.h"

namespace engine
{
  class GLcontext
  {
    GLuint _width;
    GLuint _height;
    GLfloat _near;
    GLfloat _far;
    ShaderProgram *_program;
    GLfloat _biasMatrix[16];
  public:
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
    void config(const GLuint &width, const GLuint &height, const GLfloat &near, const GLfloat &far, ShaderProgram *program);
    GLuint getProgramId(void);
    GLuint getWidth(void);
    GLuint getHeight(void);
    GLfloat getNear(void);
    GLfloat getFar(void);
    void clear(void);
  };
}


#endif
