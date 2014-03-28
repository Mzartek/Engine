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
    Vector3D(void);
    Vector3D(const T &x, const T &y, const T &z);
    ~Vector3D(void);
    void changement(const T &x, const T &y, const T &z);
    void operator=(const Vector3D &v);
    void operator+=(const Vector3D &v);
    void operator-=(const Vector3D &v);
    void operator*=(const Vector3D &v);
    void operator/=(const Vector3D &v);
    Vector3D operator+(const Vector3D &v) const;
    Vector3D operator-(const Vector3D &v) const;
    Vector3D operator*(const Vector3D &v) const;
    Vector3D operator/(const Vector3D &v) const;
    void operator=(const T &n);
    void operator+=(const T &n);
    void operator-=(const T &n);
    void operator*=(const T &n);
    void operator/=(const T &n);
    Vector3D operator+(const T &n) const;
    Vector3D operator-(const T &n) const;
    Vector3D operator*(const T &n) const;
    Vector3D operator/(const T &n) const;
  };
}

#include "Vector3D.cpp"
#endif
