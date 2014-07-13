#ifndef VECTOR2D
#define VECTOR2D

namespace engine
{
	template <typename T>
	class Vector2D
	{
	public:
		T x;
		T y;
		Vector2D(void);
		Vector2D(const T &a, const T &b);
		~Vector2D(void);
		void set(const T &a, const T &b);
		void operator=(const Vector2D &v);
		void operator+=(const Vector2D &v);
		void operator-=(const Vector2D &v);
		void operator*=(const Vector2D &v);
		void operator/=(const Vector2D &v);
		Vector2D operator+(const Vector2D &v) const;
		Vector2D operator-(const Vector2D &v) const;
		Vector2D operator*(const Vector2D &v) const;
		Vector2D operator/(const Vector2D &v) const;
		void operator=(const T &n);
		void operator+=(const T &n);
		void operator-=(const T &n);
		void operator*=(const T &n);
		void operator/=(const T &n);
		Vector2D operator+(const T &n) const;
		Vector2D operator-(const T &n) const;
		Vector2D operator*(const T &n) const;
		Vector2D operator/(const T &n) const;
	};
}

#include "Vector2D.tpp"
#endif
