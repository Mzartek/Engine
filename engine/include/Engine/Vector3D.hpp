#ifndef VECTOR3D
#define VECTOR3D

namespace engine
{
	template <typename T>
	class Vector3D
	{
	public:
		T x;
		T y;
		T z;
		Vector3D(void);
		Vector3D(const T &a, const T &b, const T &c);
		~Vector3D(void);
		void set(const T &a, const T &b, const T &c);
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

#include "Vector3D.tpp"
#endif
