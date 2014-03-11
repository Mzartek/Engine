#ifndef CAMERA
#define CAMERA

#include <cmath>
#include "Vecteur.hpp"

namespace engine
{
  class Camera
  {
  protected:
    Vecteur<double> _pcamera;
    Vecteur<double> _ptarget;
    Vecteur<double> _vforward;
    Vecteur<double> _vleft;
    double _atheta;
    double _aphi;
    double _speed;
  public:
    Camera(void);
    Camera(double x, double y, double z);
    ~Camera(void);
    void setPosition(double const &x, double const &y, double const &z);
    void setSpeed(double const &v);
    void mouseMove(int const &xrel, int const &yrel);
    void genTarget(void);
    Vecteur<double> getCamera(void) const;
    Vecteur<double> getTarget(void) const;
    Vecteur<double> getForward(void) const;
    virtual void keyboardMove(bool const &f, bool const &b, bool const &l, bool const &r) = 0;
  };
}

#endif
