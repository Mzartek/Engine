#ifndef VECTEUR
#define VECTEUR

namespace engine
{
  template <typename T>
  class Vecteur
  {
  public:
    T _x;
    T _y;
    T _z;
    T *_px;
    T *_py;
    T *_pz;
    Vecteur(void);
    Vecteur(T const &x, T const &y, T const &z);
    ~Vecteur(void);
    void changement(T const &x, T const &y, T const &z);
    void operator=(Vecteur const &v);
    void operator+=(Vecteur const &v);
    void operator-=(Vecteur const &v);
    void operator*=(Vecteur const &v);
    void operator/=(Vecteur const &v);
    Vecteur operator+(Vecteur const &v) const;
    Vecteur operator-(Vecteur const &v) const;
    Vecteur operator*(Vecteur const &v) const;
    Vecteur operator/(Vecteur const &v) const;
    void operator=(T const &n);
    void operator+=(T const &n);
    void operator-=(T const &n);
    void operator*=(T const &n);
    void operator/=(T const &n);
    Vecteur operator+(T const &n) const;
    Vecteur operator-(T const &n) const;
    Vecteur operator*(T const &n) const;
    Vecteur operator/(T const &n) const;
  };
}

#include "Vecteur.cpp"
#endif
