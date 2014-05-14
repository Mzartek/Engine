#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "Light.hpp"

namespace engine
{
  class DLLAPI SpotLight : public Light
  {
  protected:
    GLfloat _lightSpotCutOff[1];
  public:
    SpotLight(void);
    ~SpotLight(void);
    void setSpotCutOff(const float &x);
    GLfloat *getSpotCutOff(void);
    void position(void);
  };
}

#endif
