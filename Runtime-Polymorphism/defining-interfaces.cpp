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

/* Constructor injection - pass a reference to class in the constructor
 * to create the instance of the derived class */
struct Bank 
{
	Bank(Logger& logger) : logger{logger}{};  // Constructor injection
	void make_transfer(long from, long to, double amount)
	{
		// Notionally transfer funds
		logger.log_transfer(from, to, amount);
	}
	private:
		Logger& logger;
};

int main()
{
	ConsoleLogger logger;
	Bank bank{logger};   // instance of bank with logger type in constructor
	bank.make_transfer(1000, 2000, 49.95);
	bank.make_transfer(2000, 4000, 20.00);
}

