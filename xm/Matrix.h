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
}