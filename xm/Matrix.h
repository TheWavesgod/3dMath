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

		static mat4 Rotate(const vec3& axis, float radians)
		{

		}

		static mat4 Scale(const vec3& scaleVec)
		{
			mat4 result;
			result[0][0] = scaleVec.x;
			result[1][1] = scaleVec.x;
			result[2][2] = scaleVec.x;
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
}