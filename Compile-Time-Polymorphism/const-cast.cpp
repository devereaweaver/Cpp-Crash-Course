/* const_cast will actually change the value of the variable by using 
 * another reference.*/
#include <iostream>

void carbon_thaw(const int& encased_solo)
{
	std::cout << "Encased solo (before const_cast): " << encased_solo << std::endl;
	auto& hibernation_sick_solo = const_cast<int&>(encased_solo);
	hibernation_sick_solo++;
	std::cout << "Encased solo: " << encased_solo << std::endl;
	std::cout << "Hibernation sick solo: " << hibernation_sick_solo << std::endl;
}

int main()
{
	carbon_thaw(5);
}

