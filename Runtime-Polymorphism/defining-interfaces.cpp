/* defining-interfaces.cpp - demonstration on how to define 
 * and implement interaces in C++
 *
 * Create a full specified Logger interface for the banking 
 * example. 
 */
#include <iostream>

/* To declare an interface, declare a pure virtual class, 
 * to implement an interface, derive from it. 
 * Using a pure virutal class means that the derived class MUST
 * implment all of the interface's methods. This is what makes 
 * creating an interface different from regular inheritance.
 */

struct Logger    // interface, pure virtual class
{
	virtual ~Logger() = default;   // virtual destructor
	virtual void log_transfer(long from, long to, double amount) = 0; // pure virtual method
};

struct ConsoleLogger : Logger    // first Logger implementation
{
	void log_transfer(long from, long to, double amount) override
	{
		std::cout << "[console] " << from << " -> " << to << ": " 
		 	  << amount << std::endl;
	}
};

struct FileLogger : Logger     // second Logger implementation
{
	void log_transfer(long from, long to, double amount) override
	{
		std::cout << "[file] " << from << " -> " << to << ": " 
		 	  << amount << std::endl;
	}
};


int main()
{
	/* The actual injection methods are implemented in separate files */
}

