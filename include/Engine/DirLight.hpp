#ifndef DIR_LIGHT
#define DIR_LIGHT

#include "Light.hpp"

namespace engine
{
  class DirLight : public Light
  {
  public:
    DirLight(void);
    ~DirLight(void);
    void position(void);
  };
}

#endif
