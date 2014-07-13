template <typename T>
engine::Vector4D<T>::Vector4D(void)
{
  x = 0;
  y = 0;
  z = 0;
  w = 0;
}

template <typename T>
engine::Vector4D<T>::Vector4D(const T &a, const T &b, const T &c, const T &d)
{
  x = a;
  y = b;
  z = c;
  w = d;
}

template <typename T>
engine::Vector4D<T>::~Vector4D(void)
{
}

template <typename T>
void engine::Vector4D<T>::set(const T &a, const T &b, const T &c, const T &d)
{
  x = a;
  y = b;
  z = c;
  w = d;
}

template <typename T>
void engine::Vector4D<T>::operator=(const Vector4D<T> &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
}

template <typename T>
void engine::Vector4D<T>::operator+=(const Vector4D<T> &v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;
}

template <typename T>
void engine::Vector4D<T>::operator-=(const Vector4D<T> &v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;
}

template <typename T>
void engine::Vector4D<T>::operator*=(const Vector4D<T> &v)
{
  x *= v.x;
  y *= v.y;
  z *= v.z;
  w *= v.w;
}

template <typename T>
void engine::Vector4D<T>::operator/=(const Vector4D<T> &v)
{
  x /= v.x;
  y /= v.y;
  z /= v.z;
  w /= v.w;
}

template <typename T>
engine::Vector4D<T> engine::Vector4D<T>::operator+(const Vector4D<T> &v) const
{
  Vector4D<T> t = *this;
  t += v;
  return t;
}

template <typename T>
engine::Vector4D<T> engine::Vector4D<T>::operator-(const Vector4D<T> &v) const
{
  Vector4D<T> t = *this;
  t -= v;
  return t;
}

template <typename T>
engine::Vector4D<T> engine::Vector4D<T>::operator*(const Vector4D<T> &v) const
{
  Vector4D<T> t = *this;
  t *= v;
  return t;
}

template <typename T>
engine::Vector4D<T> engine::Vector4D<T>::operator/(const Vector4D<T> &v) const
{
  Vector4D<T> t = *this;
  t /= v;
  return t;
}

template <typename T>
void engine::Vector4D<T>::operator=(const T &n)
{
  x = n;
  y = n;
  z = n;
  w = n;
}

template <typename T>
void engine::Vector4D<T>::operator+=(const T &n)
{
  x += n;
  y += n;
  z += n;
  w += n;
}

template <typename T>
void engine::Vector4D<T>::operator-=(const T &n)
{
  x -= n;
  y -= n;
  z -= n;
  w -= n;
}

template <typename T>
void engine::Vector4D<T>::operator*=(const T &n)
{
  x *= n;
  y *= n;
  z *= n;
  w *= n;
}

template <typename T>
void engine::Vector4D<T>::operator/=(const T &n)
{
  x /= n;
  y /= n;
  z /= n;
  w /= n;
}

template <typename T>
engine::Vector4D<T> engine::Vector4D<T>::operator+(const T &n) const
{
  Vector4D<T> t = *this;
  t += n;
  return t;
}

template <typename T>
engine::Vector4D<T> engine::Vector4D<T>::operator-(const T &n) const
{
  Vector4D<T> t = *this;
  t -= n;
  return t;
}

template <typename T>
engine::Vector4D<T> engine::Vector4D<T>::operator*(const T &n) const
{
  Vector4D<T> t = *this;
  t *= n;
  return t;
}

template <typename T>
engine::Vector4D<T> engine::Vector4D<T>::operator/(const T &n) const
{
  Vector4D<T> t = *this;
  t /= n;
  return t;
}
