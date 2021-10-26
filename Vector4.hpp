#pragma once
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace math
{
	template <typename T>
	class Vector4
	{
	public:
		T x, y, z, w;

		Vector4() :
			x(0), y(0), z(0), w(0)
		{
		}

		Vector4(T x, T y, T z, T w) :
			x(x), y(y), z(z), w(w)
		{
		}

		Vector4(const Vector4& other) :
			x(other.x), y(other.y), z(other.z), w(other.w)
		{
		}

	public:
		float Dot(const Vector4& other)
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		Vector4 Cross(const Vector4& other)
		{
			T x = y * other.z - z * other.y;
			T y = z * other.x - x * other.z;
			T z = w * other.x - x * other.w;
			T w = x * other.x - x * other.w;
			return Vector4(x, y, z, w);
		}

		float Distance()
		{
			return sqrtf(x * x + y * y + z * z + w * w);
		}

		Vector4 Unit()
		{
			return *this / Distance();
		}

		Vector4 Lerp(const Vector4& other, float alpha)
		{
			auto lerp = [](float a, float b, float c)
			{
				return a + c * (b - a);
			};
			return Vector4(lerp(x, other.x, alpha), lerp(y, other.y, alpha), lerp(z, other.z, alpha), lerp(w, other.w, alpha));
		}

	public:
		// Plus
		Vector4 operator + (const Vector4& other)
		{
			return Vector4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
		}
		Vector4& operator += (const Vector4& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}

		// Minus
		Vector4 operator - (const Vector4& other)
		{
			return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
		}
		Vector4& operator -= (const Vector4& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this;
		}

		// Multiply
		Vector4 operator * (const Vector4& other)
		{
			return Vector4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
		}
		Vector4& operator *= (const Vector4& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;
			return *this;
		}
		Vector4 operator * (const T v)
		{
			return Vector4<T>(x * v, y * v, z * v, w * v);
		}
		Vector4& operator *= (const T v)
		{
			this->x *= v;
			this->y *= v;
			this->z *= v;
			this->w *= v;
			return *this;
		}

		// Divide
		Vector4 operator / (const Vector4& other)
		{
			return Vector4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
		}
		Vector4& operator /= (const Vector4& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;
			return *this;
		}
		Vector4 operator / (const T v)
		{
			return Vector4<T>(x / v, y / v, z / v, w / v);
		}
		Vector4& operator /= (const T v)
		{
			this->x /= v;
			this->y /= v;
			this->z /= v;
			this->w /= v;
			return *this;
		}

		// In
		friend std::istream& operator << (std::istream& istream, Vector4& v)
		{
			istream >> v.x >> v.y >> v.z >> v.w;
			return istream;
		}

		// Out
		friend std::ostream& operator << (std::ostream& ostream, const Vector4& v)
		{
			ostream << "X: " << v.x << ", Y: " << v.y << ", Z: " << v.z << ", W: " << v.w;
			return ostream;
		}

		// Vector3 Impl
	public:
		// Plus
		Vector4 operator + (const Vector3<T>& other)
		{
			return Vector4<T>(x + other.x, y + other.y, z + other.z, w);
		}
		Vector4& operator += (const Vector3<T>& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		// Minus
		Vector4 operator - (const Vector3<T>& other)
		{
			return Vector4<T>(x - other.x, y - other.y, z - other.z, w);
		}
		Vector4& operator -= (const Vector3<T>& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		// Multiply
		Vector4 operator * (const Vector3<T>& other)
		{
			return Vector4<T>(x * other.x, y * other.y, z * other.z, w);
		}
		Vector4& operator *= (const Vector3<T>& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}

		// Divide
		Vector4 operator / (const Vector3<T>& other)
		{
			return Vector4<T>(x / other.x, y / other.y, z / other.z, w);
		}
		Vector4& operator /= (const Vector3<T>& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			return *this;
		}

		// Vector2 Impl
	public:
		// Plus
		Vector4 operator + (const Vector2<T>& other)
		{
			return Vector4<T>(x + other.x, y + other.y, z);
		}
		Vector4& operator += (const Vector2<T>& other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		// Minus
		Vector4 operator - (const Vector2<T>& other)
		{
			return Vector4<T>(x - other.x, y - other.y, z);
		}
		Vector4& operator -= (const Vector2<T>& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		// Multiply
		Vector4 operator * (const Vector2<T>& other)
		{
			return Vector4<T>(x * other.x, y * other.y, z);
		}
		Vector4& operator *= (const Vector2<T>& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}

		// Divide
		Vector4 operator / (const Vector2<T>& other)
		{
			return Vector4<T>(x / other.x, y / other.y, z);
		}
		Vector4& operator /= (const Vector2<T>& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		}
	};
}