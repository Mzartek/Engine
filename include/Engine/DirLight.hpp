#ifndef DIR_LIGHT
#define DIR_LIGHT

#include "Light.hpp"

#define SIZE 50

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
