#pragma once
#include <iostream>

namespace math
{
	template <typename T = float>
	class Vector2
	{
	public:
		T x, y;

	public:
		Vector2() :
			x(0), y(0)
		{
		}

		Vector2(T x, T y) :
			x(x), y(y)
		{
		}

		Vector2(const Vector2& other) :
			x(other.x), y(other.y)
		{
		}

	public:
		float Dot(const Vector2& other)
		{
			return x * other.x + y * other.y;
		}

		float Cross(const Vector2& other)
		{
			return x * other.y - y * other.x;
		}

		float Distance()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2 Unit()
		{
			return this / Distance();
		}

		Vector2 Lerp(const Vector2& other, float alpha)
		{
			auto lerp = [](float a, float b, float c)
			{
				return a + c * (b - a);
			};
			return Vector2(lerp(x, other.x, alpha), lerp(y, other.y, alpha));
		}

	public:
		// Plus
		Vector2 operator + (const Vector2& other)
		{
			return Vector2<T>(x + other.x, y + other.y);
		}
		Vector2& operator += (const Vector2& other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		// Minus
		Vector2 operator - (const Vector2& other)
		{
			return Vector2<T>(x - other.x, y - other.y);
		}
		Vector2& operator -= (const Vector2& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		// Multiply
		Vector2 operator * (const Vector2& other)
		{
			return Vector2<T>(x * other.x, y * other.y);
		}
		Vector2& operator *= (const Vector2& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}
		Vector2 operator * (const T v)
		{
			return Vector2<T>(x * v, y * v);
		}
		Vector2& operator *= (const T v)
		{
			this->x *= v;
			this->y *= v;
			return *this;
		}

		// Divide
		Vector2 operator / (const Vector2& other)
		{
			return Vector2<T>(x / other.x, y / other.y);
		}
		Vector2& operator /= (const Vector2& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		}
		Vector2 operator / (const T v)
		{
			return Vector2<T>(x / v, y / v);
		}
		Vector2& operator /= (const T v)
		{
			this->x /= v;
			this->y /= v;
			return *this;
		}

		// In
		friend std::istream& operator << (std::istream& istream, Vector2& v)
		{
			istream >> v.x >> v.y;
			return istream;
		}

		// Out
		friend std::ostream& operator << (std::ostream& ostream, const Vector2& v)
		{
			ostream << "X: " << v.x << ", Y: " << v.y;
			return ostream;
		}
	};
}