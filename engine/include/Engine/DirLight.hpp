#ifndef DIR_LIGHT
#define DIR_LIGHT

#include "Light.hpp"

namespace engine
{
  class DirLight : public Light
  {
  private:
    GLfloat _dim[3];
  public:
    DirLight(void);
    ~DirLight(void);
    void setDimension(GLfloat x, GLfloat y, GLfloat z);
    void position(void);
  };
}

#endif
