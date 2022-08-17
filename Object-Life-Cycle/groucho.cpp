/* Example of throwing an exception */
#include <iostream>
#include <stdexcept>
#include <cstdio>

/* Groucho will throw an exception whenever you invoke 
 * the forget method with an argument equal to 0xFACE */

struct Groucho
{
	void forget(int x)
	{
		if (x == 0xFACE)    // throw exception if equality holds
		{
			throw std::runtime_error{"I'd be glad to make an exception."};
		}
		printf("Forgot 0x%x\n", x);    // else print argument
	}
};

int main()
{
	Groucho groucho;

	try
	{
		groucho.forget(0xC0DE);
		groucho.forget(0xFACE);    // exception in flight!
		groucho.forget(0xC0FFEE);
	}
	catch (const std::runtime_error& e)    // catch, exception handler
	{
		// catch and print error message
		printf("Exception caught with message: %s\n", e.what());
	}
}

