#include <stdio.h>
#include <array>
#include <iostream>

template <int N>
constexpr int det(const std::array<std::array<int, N>, N>& a)
{
	if constexpr (N == 1)
	{
		return a[0][0];
	}
	else if constexpr (N > 1)
	{
		int determinator = 0, temp_res = 0;
		std::array<std::array<int, N-1>, N-1> temp_matrix{};

		for (int i = 0; i < N; ++i)
		{
			for (int j = 1; j < N; ++j)
			{
				for (int k = 0; k < N; ++k)
				{
					if (k == i)
					{
						continue;
					}
					temp_matrix[j][k] = a[j][k];
				}
			}
			temp_res = a[0][i];
			temp_res = temp_res * det<N-1>(temp_matrix);
			determinator += (i % 2 == 0) ? temp_res : -temp_res;
		}

		return determinator;
	}
	else
	{
		return 0;
	}
}

int main()
{
	std::array<std::array<int, 3>, 3> A = {{
			{0, 1, 2},
		   	{1, 2, 3},
			{2, 3, 7}
	}};
	constexpr int res = det<3>(A);
}