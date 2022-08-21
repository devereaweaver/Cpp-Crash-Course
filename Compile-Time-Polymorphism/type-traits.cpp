/* demonstration on how to use type traits to ensure compile
 * time type checking for templates;
 * type traits tell you what types are, but not how the 
 * template will use them
 */
#include <iostream>
#include <type_traits>
#include <cstdint>

// print out boolean value as a string
constexpr const char* as_str(bool x)
{
	return x ? "True" : "False";
}

int main()
{
	/* it basically tests what type we are dealing wtih */
	std::cout << as_str(std::is_integral<int>::value) << std::endl;
	std::cout << as_str(std::is_integral<const int>::value) << std::endl;
	std::cout << as_str(std::is_integral<float>::value) << std::endl;
}

