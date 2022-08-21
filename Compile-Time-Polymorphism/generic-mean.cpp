#include <iostream>

/* implement generic version of mean function */
template<typename T>
T mean(const T* values, size_t length)
{
	T result{};
	for(size_t i{}; i < length; i++)
	{
		result += values[i];
	}
	return result/length;
}

int main()
{
	const double nums_d[]{1.0, 2.0, 3.0, 4.0};
	const auto result1 = mean(nums_d, 4);
	std::cout << "Double: " << result1 << std::endl;	

	const float nums_f[]{1.0f, 2.0f, 3.0f, 4.0f};
	const auto result2 = mean(nums_f, 4);
	std::cout << "Float: " << result2 << std::endl;	

	// includes unecessary type declaration
	const size_t nums_c[]{1, 2, 3, 4};
	const auto result3 = mean<size_t>(nums_c, 4);
	std::cout << "Size_t: " << result3 << std::endl;
}
