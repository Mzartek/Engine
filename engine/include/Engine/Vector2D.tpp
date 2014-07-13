template <typename T>
engine::Vector2D<T>::Vector2D(void)
{
  x = 0;
  y = 0;
}

template <typename T>
engine::Vector2D<T>::Vector2D(const T &a, const T &b)
{
  x = a;
  y = b;
}

template <typename T>
engine::Vector2D<T>::~Vector2D(void)
{
}

template <typename T>
void engine::Vector2D<T>::set(const T &a, const T &b)
{
  x = a;
  y = b;
}

template <typename T>
void engine::Vector2D<T>::operator=(const Vector2D<T> &v)
{
  x = v.x;
  y = v.y;
}

template <typename T>
void engine::Vector2D<T>::operator+=(const Vector2D<T> &v)
{
  x += v.x;
  y += v.y;
}

template <typename T>
void engine::Vector2D<T>::operator-=(const Vector2D<T> &v)
{
  x -= v.x;
  y -= v.y;
}

template <typename T>
void engine::Vector2D<T>::operator*=(const Vector2D<T> &v)
{
  x *= v.x;
  y *= v.y;
}

template <typename T>
void engine::Vector2D<T>::operator/=(const Vector2D<T> &v)
{
  x /= v.x;
  y /= v.y;
}

template <typename T>
engine::Vector2D<T> engine::Vector2D<T>::operator+(const Vector2D<T> &v) const
{
  Vector2D<T> t = *this;
  t += v;
  return t;
}

template <typename T>
engine::Vector2D<T> engine::Vector2D<T>::operator-(const Vector2D<T> &v) const
{
  Vector2D<T> t = *this;
  t -= v;
  return t;
}

template <typename T>
engine::Vector2D<T> engine::Vector2D<T>::operator*(const Vector2D<T> &v) const
{
  Vector2D<T> t = *this;
  t *= v;
  return t;
}

template <typename T>
engine::Vector2D<T> engine::Vector2D<T>::operator/(const Vector2D<T> &v) const
{
  Vector2D<T> t = *this;
  t /= v;
  return t;
}

template <typename T>
void engine::Vector2D<T>::operator=(const T &n)
{
  x = n;
  y = n;
}

template <typename T>
void engine::Vector2D<T>::operator+=(const T &n)
{
  x += n;
  y += n;
}

template <typename T>
void engine::Vector2D<T>::operator-=(const T &n)
{
  x -= n;
  y -= n;
}

template <typename T>
void engine::Vector2D<T>::operator*=(const T &n)
{
  x *= n;
  y *= n;
}

template <typename T>
void engine::Vector2D<T>::operator/=(const T &n)
{
  x /= n;
  y /= n;
}

template <typename T>
engine::Vector2D<T> engine::Vector2D<T>::operator+(const T &n) const
{
  Vector2D<T> t = *this;
  t += n;
  return t;
}

template <typename T>
engine::Vector2D<T> engine::Vector2D<T>::operator-(const T &n) const
{
  Vector2D<T> t = *this;
  t -= n;
  return t;
}

template <typename T>
engine::Vector2D<T> engine::Vector2D<T>::operator*(const T &n) const
{
  Vector2D<T> t = *this;
  t *= n;
  return t;
}

template <typename T>
engine::Vector2D<T> engine::Vector2D<T>::operator/(const T &n) const
{
  Vector2D<T> t = *this;
  t /= n;
  return t;
}
