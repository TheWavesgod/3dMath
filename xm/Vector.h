#pragma once

#include <array>
#include <stdexcept>
#include <cmath>

namespace xm
{
	class vec3
	{
	public:
		union 
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			std::array<float, 3> data;
		};

		vec3() : x(0), y(0), z(0) {}

		vec3(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}

		float& operator[](int i) { return data[i]; }
		float operator[](int i) const { return data[i]; }

		vec3 operator-() const { return vec3(-x, -y, -z); }
		vec3 operator+(const vec3& v) { return vec3(x + v.x, y + v.y, z + v.z); }
		vec3 operator-(const vec3& v) { return vec3(x - v.x, y - v.y, z - v.z); }

		vec3 operator*(float k) const { return vec3(k * x, k * y, k * z); }
		vec3 operator/(float k) const {
			float oneOverK = 1 / k;
			return vec3(oneOverK * x, oneOverK * y, oneOverK * z);
		}

		float operator*(const vec3& v) const { return x * v.x + y * v.y + z * v.z; }

		float length() { return sqrt(x * x + y * y + z * z); }

		void normalized()
		{
			float len = length();
			if (len == 0) return;
			float oneOverlen = 1 / len;
			x *= oneOverlen;
			y *= oneOverlen;
			z *= oneOverlen;
		}
	};

	float Dot(const vec3& A, const vec3& B) { return A.x * B.x + A.y * B.y + A.z * B.z; }

	vec3 Cross(const vec3& A, const vec3& B)
	{
		vec3 result;
		result[0] = A[1] * B[2] - A[2] * B[1];
		result[1] = A[2] * B[0] - A[0] * B[2];
		result[2] = A[0] * B[1] - A[1] * B[0];
	}
}