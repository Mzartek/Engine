#ifndef VECTEUR
#define VECTEUR

namespace engine
{
  template <typename T>
  class Vector3D
  {
  public:
    T _x;
    T _y;
    T _z;
    T *_px;
    T *_py;
    T *_pz;
    Vector3D(void);
    Vector3D(T const &x, T const &y, T const &z);
    ~Vector3D(void);
    void changement(T const &x, T const &y, T const &z);
    void operator=(Vector3D const &v);
    void operator+=(Vector3D const &v);
    void operator-=(Vector3D const &v);
    void operator*=(Vector3D const &v);
    void operator/=(Vector3D const &v);
    Vector3D operator+(Vector3D const &v) const;
    Vector3D operator-(Vector3D const &v) const;
    Vector3D operator*(Vector3D const &v) const;
    Vector3D operator/(Vector3D const &v) const;
    void operator=(T const &n);
    void operator+=(T const &n);
    void operator-=(T const &n);
    void operator*=(T const &n);
    void operator/=(T const &n);
    Vector3D operator+(T const &n) const;
    Vector3D operator-(T const &n) const;
    Vector3D operator*(T const &n) const;
    Vector3D operator/(T const &n) const;
  };
}

#include "Vector3D.cpp"
#endif
