template <typename T>
engine::Vector3D<T>::Vector3D(void)
{
  x = 0;
  y = 0;
  z = 0;
}

template <typename T>
engine::Vector3D<T>::Vector3D(const T &a, const T &b, const T &c)
{
  x = a;
  y = b;
  z = c;
}

template <typename T>
engine::Vector3D<T>::~Vector3D(void)
{
}

template <typename T>
void engine::Vector3D<T>::set(const T &a, const T &b, const T &c)
{
  x = a;
  y = b;
  z = c;
}

template <typename T>
void engine::Vector3D<T>::operator=(const Vector3D<T> &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
}

template <typename T>
void engine::Vector3D<T>::operator+=(const Vector3D<T> &v)
{
  x += v.x;
  y += v.y;
  z += v.z;
}

template <typename T>
void engine::Vector3D<T>::operator-=(const Vector3D<T> &v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

template <typename T>
void engine::Vector3D<T>::operator*=(const Vector3D<T> &v)
{
  x *= v.x;
  y *= v.y;
  z *= v.z;
}

template <typename T>
void engine::Vector3D<T>::operator/=(const Vector3D<T> &v)
{
  x /= v.x;
  y /= v.y;
  z /= v.z;
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
  x = n;
  y = n;
  z = n;
}

template <typename T>
void engine::Vector3D<T>::operator+=(const T &n)
{
  x += n;
  y += n;
  z += n;
}

template <typename T>
void engine::Vector3D<T>::operator-=(const T &n)
{
  x -= n;
  y -= n;
  z -= n;
}

template <typename T>
void engine::Vector3D<T>::operator*=(const T &n)
{
  x *= n;
  y *= n;
  z *= n;
}

template <typename T>
void engine::Vector3D<T>::operator/=(const T &n)
{
  x /= n;
  y /= n;
  z /= n;
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
