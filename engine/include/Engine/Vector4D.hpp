#ifndef VECTOR4D
#define VECTOR4D

namespace engine
{
	template <typename T>
	class Vector4D
	{
	public:
		T x;
		T y;
		T z;
		T w;
		Vector4D(void);
		Vector4D(const T &a, const T &b, const T &c, const T &d);
		~Vector4D(void);
		void set(const T &a, const T &b, const T &c, const T &d);
		void operator=(const Vector4D &v);
		void operator+=(const Vector4D &v);
		void operator-=(const Vector4D &v);
		void operator*=(const Vector4D &v);
		void operator/=(const Vector4D &v);
		Vector4D operator+(const Vector4D &v) const;
		Vector4D operator-(const Vector4D &v) const;
		Vector4D operator*(const Vector4D &v) const;
		Vector4D operator/(const Vector4D &v) const;
		void operator=(const T &n);
		void operator+=(const T &n);
		void operator-=(const T &n);
		void operator*=(const T &n);
		void operator/=(const T &n);
		Vector4D operator+(const T &n) const;
		Vector4D operator-(const T &n) const;
		Vector4D operator*(const T &n) const;
		Vector4D operator/(const T &n) const;
	};
}

#include "Vector4D.tpp"
#endif
