#pragma once

#include "Vector.h"

namespace xm
{
	template<size_t N>
	class Matrix
	{
	private:
		std::array<std::array<float, N>, N> data;

	public:
		Matrix()
		{
			for (auto& row : data)
			{
				row.fill(0.0f);
			}
		}

		std::array<float, N>& operator[](size_t row)
		{
			if (row >= N) { throw std::out_of_range("Row index out of range"); }
			return data[row];
		}

		const std::array<float, N> operator[](size_t row) const 
		{
			if (row >= N) { throw std::out_of_range("Row index out of range"); }
			return data[row];
		}

		Matrix<N> operator*(const Matrix<N>& m) const 
		{
			Matrix<N> result;
			for (size_t i = 0; i < N; ++i)
			{
				for (size_t j = 0; j < N; ++j)
				{
					for (size_t k = 0; k < N; ++k)
					{
						result[i][j] += data[i][k] * m.data[k][j];
					}
				}
			}

			return result;
		}
	};

	using mat2 = Matrix<2>;
	using mat3 = Matrix<3>;
	using mat4 = Matrix<4>;

	template<>
	class Matrix<4>
	{
	private:
		std::array<std::array<float, 4>, 4> data;

	public:
		Matrix<4>()
		{
			for (auto& row : data)
			{
				row.fill(0.0f);
			}
		}

		std::array<float, 4>& operator[](size_t row)
		{
			if (row >= 4) { throw std::out_of_range("Row index out of range"); }
			return data[row];
		}

		const std::array<float, 4> operator[](size_t row) const
		{
			if (row >= 4) { throw std::out_of_range("Row index out of range"); }
			return data[row];
		}

		mat4 operator *(const mat4& m) const
		{
			mat4 result;
			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t j = 0; j < 4; ++j)
				{
					for (size_t k = 0; k < 4; ++k)
					{
						result.data[i][j] += data[i][k] * m.data[k][j];
					}
				}
			}
			return result;
		}

		vec4 operator*(const vec4& vec) const 
		{
			vec4 result;
			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t k = 0; k < 4; ++k)
				{
					result.data[i] += data[i][k] * vec.data[k];
				}
			}
			return result;
		}

		float determinant()
		{
			return 0.0f;
		}

		static mat4 Transport(const vec3& displacment)
		{
			mat4 result;
			result[0][0] = 1;
			result[1][1] = 1;
			result[2][2] = 1;
			result[3][3] = 1;
			result[0][3] = displacment.x;
			result[1][3] = displacment.y;
			result[2][3] = displacment.z;
			return result;
		}

		static mat4 Rotate(const vec3& axis, float radians)
		{
			mat4 result;
			float c = cos(radians);
			float s = sin(radians);
			float x = axis.x;
			float y = axis.y;
			float z = axis.z;
			result[0][0] = c + (1 - c) * x * x;
			result[0][1] = (1 - c) * x * y - s * z;
			result[0][2] = (1 - c) * x * z - s * y;
			result[1][0] = (1 - c) * x * y + s * z;
			result[1][1] = c + (1 - c) * y * y;
			result[1][2] = (1 - c) * y * z - s * x;
			result[2][0] = (1 - c) * x * z - s * y;
			result[2][1] = (1 - c) * y * z + s * x;
			result[2][2] = c + (1 - c) * z * z;
			result[3][3] = 1.0f;
		}

		static mat4 Scale(const vec3& scaleVec)
		{
			mat4 result;
			result[0][0] = scaleVec.x;
			result[1][1] = scaleVec.y;
			result[2][2] = scaleVec.z;
			result[3][3] = 1.0f;	
			return result;
		}
	};

	template<size_t N>
	Matrix<N> toMat4(const vector<3> axis, float radians)
	{
		static_assert(N == 4);
		Matrix<N> result;
		if constexpr (N == 4)
		{

		}
		return result;
	}

	template<size_t N>
	void Print(const Matrix<N>& mat) 
	{
		using namespace std;
		cout << "Matrix: " << endl;
		for (size_t i = 0; i < N; ++i)
		{
			cout << "| ";
			for (size_t j = 0; j < N; ++j)
			{
				cout << " " << mat[i][j] << " ";
			}
			cout << "|";
		}
	}
}