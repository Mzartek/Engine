#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "Light.hpp"

namespace engine
{
  class SpotLight : public Light
  {
  protected:
    GLfloat _lightSpotCutOff[1];
  public:
    SpotLight(void);
    ~SpotLight(void);
    void setCone(const float &x);
    void position(void);
  };
}

#endif
