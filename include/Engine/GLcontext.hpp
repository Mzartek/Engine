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
    void setProjectionMatrixLocation(ShaderProgram *program, char const *name);
    void adjust(int const &w, int const &h, float const &fov, float const &near, float const &far);
  };
}


#endif
