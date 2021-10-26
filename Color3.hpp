#pragma once
#include <iostream>
#include <cmath>

namespace graphics
{
	class Color3
	{
	private:
		void clamp_values()
		{
			R = (unsigned char)fminl(R, fmax(R, 255));
			G = (unsigned char)fminl(G, fmax(G, 255));
			B = (unsigned char)fminl(B, fmax(B, 255));
		}

	public:
		unsigned char R, G, B;

	public:
		Color3() :
			R(0), G(0), B(0)
		{
			clamp_values();
		}

		Color3(unsigned char Red, unsigned char Green, unsigned char Blue) :
			R(Red), G(Green), B(Blue)
		{
			clamp_values();
		}

		Color3(const Color3& other) :
			R(other.R), G(other.G), B(other.B)
		{
			clamp_values();
		}

	public:
		Color3 Lerp(const Color3& other, float alpha)
		{
			auto lerp = [](float a, float b, float c) 
			{
				return a + c * (b - a);
			};
			return Color3(lerp(R, other.R, alpha), lerp(G, other.G, alpha), lerp(B, other.B, alpha));
		}

	public:
		// Plus
		Color3 operator + (const Color3& other)
		{
			return Color3(R + other.R, G + other.G, B + other.B);
		}
		Color3& operator += (const Color3& other)
		{
			this->R += other.R;
			this->G += other.G;
			this->B += other.B;
			clamp_values();
			return *this;
		}

		// Minus
		Color3 operator - (const Color3& other)
		{
			return Color3(R - other.R, G - other.G, B - other.B);
		}
		Color3& operator -= (const Color3& other)
		{
			this->R -= other.R;
			this->G -= other.G;
			this->B -= other.B;
			clamp_values();
			return *this;
		}

		// MultiplG
		Color3 operator * (const Color3& other)
		{
			return Color3(R * other.R, G * other.G, B * other.B);
		}
		Color3& operator *= (const Color3& other)
		{
			this->R *= other.R;
			this->G *= other.G;
			this->B *= other.B;
			clamp_values();
			return *this;
		}
		Color3 operator * (const unsigned char v)
		{
			return Color3(R * v, G * v, B * v);
		}
		Color3& operator *= (const unsigned char v)
		{
			this->R *= v;
			this->G *= v;
			this->B *= v;
			clamp_values();
			return *this;
		}

		// Divide
		Color3 operator / (const Color3& other)
		{
			return Color3(R / other.R, G / other.G, B / other.B);
		}
		Color3& operator /= (const Color3& other)
		{
			this->R /= other.R;
			this->G /= other.G;
			this->B /= other.B;
			clamp_values();
			return *this;
		}
		Color3 operator / (const unsigned char v)
		{
			return Color3(R / v, G / v, B / v);
		}
		Color3& operator /= (const unsigned char v)
		{
			this->R /= v;
			this->G /= v;
			this->B /= v;
			clamp_values();
			return *this;
		}

		// In
		friend std::istream& operator << (std::istream& istream, Color3& v)
		{
			istream >> v.R >> v.G >> v.B;
			v.clamp_values();
			return istream;
		}

		// Out
		friend std::ostream& operator << (std::ostream& ostream, const Color3& v)
		{
			ostream << "R: " << (unsigned int)v.R << ", G: " << (unsigned int)v.G << ", B: " << (unsigned int)v.B;
			return ostream;
		}
	};
}