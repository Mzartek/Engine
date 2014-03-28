template <typename T>
engine::Vector3D<T>::Vector3D(void)
{
  _x = 0;
  _y = 0;
  _z = 0;
}

template <typename T>
engine::Vector3D<T>::Vector3D(const T &x, const T &y, const T &z)
{
  _x = x;
  _y = y;
  _z = z;
}

template <typename T>
engine::Vector3D<T>::~Vector3D(void)
{
}

template <typename T>
void engine::Vector3D<T>::changement(const T &x, const T &y, const T &z)
{
  _x = x;
  _y = y;
  _z = z;
}

template <typename T>
void engine::Vector3D<T>::operator=(const Vector3D<T> &v)
{
  _x = v._x;
  _y = v._y;
  _z = v._z;
}

template <typename T>
void engine::Vector3D<T>::operator+=(const Vector3D<T> &v)
{
  _x += v._x;
  _y += v._y;
  _z += v._z;
}

template <typename T>
void engine::Vector3D<T>::operator-=(const Vector3D<T> &v)
{
  _x -= v._x;
  _y -= v._y;
  _z -= v._z;
}

template <typename T>
void engine::Vector3D<T>::operator*=(const Vector3D<T> &v)
{
  _x *= v._x;
  _y *= v._y;
  _z *= v._z;
}

template <typename T>
void engine::Vector3D<T>::operator/=(const Vector3D<T> &v)
{
  _x /= v._x;
  _y /= v._y;
  _z /= v._z;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator+(const Vector3D<T> &v) const
{
  Vector3D<T> t = *this;
  t += v;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator-(const Vector3D<T> &v) const
{
  Vector3D<T> t = *this;
  t -= v;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator*(const Vector3D<T> &v) const
{
  Vector3D<T> t = *this;
  t *= v;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator/(const Vector3D<T> &v) const
{
  Vector3D<T> t = *this;
  t /= v;
  return t;
}

template <typename T>
void engine::Vector3D<T>::operator=(const T &n)
{
  _x = n;
  _y = n;
  _z = n;
}

template <typename T>
void engine::Vector3D<T>::operator+=(const T &n)
{
  _x += n;
  _y += n;
  _z += n;
}

template <typename T>
void engine::Vector3D<T>::operator-=(const T &n)
{
  _x -= n;
  _y -= n;
  _z -= n;
}

template <typename T>
void engine::Vector3D<T>::operator*=(const T &n)
{
  _x *= n;
  _y *= n;
  _z *= n;
}

template <typename T>
void engine::Vector3D<T>::operator/=(const T &n)
{
  _x /= n;
  _y /= n;
  _z /= n;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator+(const T &n) const
{
  Vector3D<T> t = *this;
  t += n;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator-(const T &n) const
{
  Vector3D<T> t = *this;
  t -= n;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator*(const T &n) const
{
  Vector3D<T> t = *this;
  t *= n;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator/(const T &n) const
{
  Vector3D<T> t = *this;
  t /= n;
  return t;
}
