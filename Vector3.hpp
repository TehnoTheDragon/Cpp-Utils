#pragma once
#include "Vector2.hpp"

namespace math
{
	template <typename T>
	class Vector3
	{
	public:
		T x, y, z;

	public:
		Vector3() :
			x(0), y(0), z(0)
		{
		}

		Vector3(T x, T y, T z) :
			x(x), y(y), z(z)
		{
		}

		Vector3(const Vector3& other) :
			x(other.x), y(other.y), z(other.z)
		{
		}

	public:
		float Dot(const Vector3& other)
		{
			return x * other.x + y * other.y + z * other.z;
		}

		Vector3 Cross(const Vector3& other)
		{
			T x = y * other.z - z * other.y;
			T y = z * other.x - x * other.z;
			T z = x * other.y - y * other.x;
			return Vector3(x, y, z);
		}

		float Distance()
		{
			return sqrtf(x * x + y * y + z * z);
		}

		Vector3 Unit()
		{
			return *this / Distance();
		}

		Vector3 Lerp(const Vector3& other, float alpha)
		{
			auto lerp = [](float a, float b, float c)
			{
				return a + c * (b - a);
			};
			return Vector3(lerp(x, other.x, alpha), lerp(y, other.y, alpha), lerp(z, other.z, alpha));
		}

	public:
		// Plus
		Vector3 operator + (const Vector3& other)
		{
			return Vector3<T>(x + other.x, y + other.y, z + other.z);
		}
		Vector3& operator += (const Vector3& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		// Minus
		Vector3 operator - (const Vector3& other)
		{
			return Vector3<T>(x - other.x, y - other.y, z - other.z);
		}
		Vector3& operator -= (const Vector3& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		// Multiply
		Vector3 operator * (const Vector3& other)
		{
			return Vector3<T>(x * other.x, y * other.y, z * other.z);
		}
		Vector3& operator *= (const Vector3& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}
		Vector3 operator * (const T v)
		{
			return Vector3<T>(x * v, y * v, z * v);
		}
		Vector3& operator *= (const T v)
		{
			this->x *= v;
			this->y *= v;
			this->z *= v;
			return *this;
		}

		// Divide
		Vector3 operator / (const Vector3& other)
		{
			return Vector3<T>(x / other.x, y / other.y, z / other.z);
		}
		Vector3& operator /= (const Vector3& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			return *this;
		}
		Vector3 operator / (const T v)
		{
			return Vector3<T>(x / v, y / v, z / v);
		}
		Vector3& operator /= (const T v)
		{
			this->x /= v;
			this->y /= v;
			this->z /= v;
			return *this;
		}

		// In
		friend std::istream& operator << (std::istream& istream, Vector3& v)
		{
			istream >> v.x >> v.y >> v.z;
			return istream;
		}

		// Out
		friend std::ostream& operator << (std::ostream& ostream, const Vector3& v)
		{
			ostream << "X: " << v.x << ", Y: " << v.y << ", Z: " << v.z;
			return ostream;
		}

		// Vector2 Impl
	public:
		// Plus
		Vector3 operator + (const Vector2<T>& other)
		{
			return Vector3<T>(x + other.x, y + other.y, z);
		}
		Vector3& operator += (const Vector2<T>& other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		// Minus
		Vector3 operator - (const Vector2<T>& other)
		{
			return Vector3<T>(x - other.x, y - other.y, z);
		}
		Vector3& operator -= (const Vector2<T>& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		// Multiply
		Vector3 operator * (const Vector2<T>& other)
		{
			return Vector3<T>(x * other.x, y * other.y, z);
		}
		Vector3& operator *= (const Vector2<T>& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}

		// Divide
		Vector3 operator / (const Vector2<T>& other)
		{
			return Vector3<T>(x / other.x, y / other.y, z);
		}
		Vector3& operator /= (const Vector2<T>& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		}
	};
}