#pragma once

#include <array>
#include <stdexcept>
#include <cmath>
#include <iostream>

namespace xm
{
	template <size_t N>
	class vector
	{
	public:
		vector() { data.fill(0.0f); }

		float operator [](int i) { return data[i]; }
		float operator [](int i) const { return data[i]; }

		std::array<float, N> data;
	};

	template <>
	class vector<3>
	{
	public:
		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			std::array<float, 3> data;
		};

		vector() : x(0), y(0), z(0) {}

		vector(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}

		float operator [](int i) { return data[i]; }
		float operator [](int i) const { return data[i]; }

		vector<3> operator -() const { return vector<3>(-x, -y, -z); }

		vector<3> operator +(const vector<3>& v) const { return vector<3>(x + v.x, y + v.y, z + v.z); }

		vector<3> operator -(const vector<3>& v) const { return vector<3>(x - v.x, y - v.y, z - v.z); }

		vector<3> operator *(float k) const { return vector<3>(k * x, k * y, k * z); }

		vector<3> operator /(float k) const {
			float oneOverK = 1 / k;
			return vector<3>(oneOverK * x, oneOverK * y, oneOverK * z);
		}

		float operator *(const vector<3>& v) const { return x * v.x + y * v.y + z * v.z; }

		float length() const { return sqrt(x * x + y * y + z * z); }

		void nomalized()
		{
			float len = length();
			if (len == 0) return;
			float oneOverlen = 1 / len;
			x *= oneOverlen;
			y *= oneOverlen;
			z *= oneOverlen;
		}

		vector<3> projectTo(const vector<3>& tar) const
		{
			float dotResult = x * tar.x + y * tar.y + z * tar.z;
			float squareTar = tar.x * tar.x + tar.y * tar.y + tar.z * tar.z;
			return tar * (dotResult / squareTar);
		}

		vector<3> cross(const vector<3>& vec) const 
		{
			return vector<3>(
				y * vec.z - z * vec.y,
				z * vec.x - x * vec.z,
				x * vec.y - y * vec.x
			);
		}

		float dot(const vector<3>& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}
	};

	template <>
	class vector<4>
	{
	public:
		union
		{
			struct { float x, y, z, w; };
			std::array<float, 4> data;
		};
	};

	template<size_t N>
	vector<N> operator *(float k, const vector<N>& v)
	{
		vector<N> result;
		for (size_t i = 0; i < N; ++i)
		{
			result.data[i] = k * v.data[i];
		}
		return result;
	}

	template<size_t N>
	float Dot(const vector<N>& A, const vector<N>& B)
	{
		float result = 0;
		for (size_t i = 0; i < N; ++i)
		{
			result += A.data[i] * B.data[i];
		}
		return result;
	}

	template<size_t N>
	vector<N> Cross(const vector<N>& A, const vector<N>& B)
	{
		static_assert(N == 3, "Only vec3 can use Cross production.");
		vector<N> result;
		if constexpr (N == 3)
		{
			result[0] = A[1] * B[2] - A[2] * B[1];
			result[1] = A[2] * B[0] - A[0] * B[2];
			result[2] = A[0] * B[1] - A[1] * B[0];
		}
		return result;
	}

	using vec2 = vector<2>;
	using vec3 = vector<3>;
	using vec4 = vector<4>;
}