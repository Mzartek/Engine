template <typename T>
engine::Vecteur<T>::Vecteur(void)
{
  _x=0;
  _y=0;
  _z=0;
  _px=&_x;
  _py=&_y;
  _pz=&_z;
}

template <typename T>
engine::Vecteur<T>::Vecteur(T const &x, T const &y, T const &z)
{
  _x=x;
  _y=y;
  _z=z;
  _px=&_x;
  _py=&_y;
  _pz=&_z;
}

template <typename T>
engine::Vecteur<T>::~Vecteur(void)
{
}

template <typename T>
void engine::Vecteur<T>::changement(T const &x, T const &y, T const &z)
{
  _x = x;
  _y = y;
  _z = z;
}

template <typename T>
void engine::Vecteur<T>::operator=(Vecteur<T> const &v)
{
  _x = v._x;
  _y = v._y;
  _z = v._z;
}

template <typename T>
void engine::Vecteur<T>::operator+=(Vecteur<T> const &v)
{
  _x += v._x;
  _y += v._y;
  _z += v._z;
}

template <typename T>
void engine::Vecteur<T>::operator-=(Vecteur<T> const &v)
{
  _x -= v._x;
  _y -= v._y;
  _z -= v._z;
}

template <typename T>
void engine::Vecteur<T>::operator*=(Vecteur<T> const &v)
{
  _x *= v._x;
  _y *= v._y;
  _z *= v._z;
}

template <typename T>
void engine::Vecteur<T>::operator/=(Vecteur<T> const &v)
{
  _x /= v._x;
  _y /= v._y;
  _z /= v._z;
}

template <typename T>
engine::Vecteur<T> engine::Vecteur<T>::operator+(Vecteur<T> const &v) const
{
  Vecteur<T> t = *this;
  t += v;
  return t;
}

template <typename T>
engine::Vecteur<T> engine::Vecteur<T>::operator-(Vecteur<T> const &v) const
{
  Vecteur<T> t = *this;
  t -= v;
  return t;
}

template <typename T>
engine::Vecteur<T> engine::Vecteur<T>::operator*(Vecteur<T> const &v) const
{
  Vecteur<T> t = *this;
  t *= v;
  return t;
}

template <typename T>
engine::Vecteur<T> engine::Vecteur<T>::operator/(Vecteur<T> const &v) const
{
  Vecteur<T> t = *this;
  t /= v;
  return t;
}

template <typename T>
void engine::Vecteur<T>::operator=(T const &n)
{
  _x = n;
  _y = n;
  _z = n;
}

template <typename T>
void engine::Vecteur<T>::operator+=(T const &n)
{
  _x += n;
  _y += n;
  _z += n;
}

template <typename T>
void engine::Vecteur<T>::operator-=(T const &n)
{
  _x -= n;
  _y -= n;
  _z -= n;
}

template <typename T>
void engine::Vecteur<T>::operator*=(T const &n)
{
  _x *= n;
  _y *= n;
  _z *= n;
}

template <typename T>
void engine::Vecteur<T>::operator/=(const T &n)
{
  _x /= n;
  _y /= n;
  _z /= n;
}

template <typename T>
engine::Vecteur<T> engine::Vecteur<T>::operator+(T const &n) const
{
  Vecteur<T> t = *this;
  t += n;
  return t;
}

template <typename T>
engine::Vecteur<T> engine::Vecteur<T>::operator-(T const &n) const
{
  Vecteur<T> t = *this;
  t -= n;
  return t;
}

template <typename T>
engine::Vecteur<T> engine::Vecteur<T>::operator*(T const &n) const
{
  Vecteur<T> t = *this;
  t *= n;
  return t;
}

template <typename T>
engine::Vecteur<T> engine::Vecteur<T>::operator/(T const &n) const
{
  Vecteur<T> t = *this;
  t /= n;
  return t;
}
