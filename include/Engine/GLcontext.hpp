#ifndef GL_CONTEXT
#define GL_CONTEXT

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GL.hpp"
#include "ShaderProgram.hpp"

namespace engine
{
  class GLcontext
  {
  private:
    ShaderProgram *_program;
    GLint _projectionMatrixLocation;
    glm::mat4 _projectionMatrix;
  public:
    GLcontext(void);
    ~GLcontext(void);
    void setShaderProgram(ShaderProgram *program);
    void adjust(const int &w, const int &h, const float &fov, const float &near, const float &far);
  };
}


#endif
