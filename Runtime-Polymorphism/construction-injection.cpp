/* construction-injection.cpp - example using construction injection
 * for an interface */
#include <iostream>

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

/* This example sets the value of logger member (the derived class)
 * in the constructor using a member initialization list 
 * This is useful since we have to use a reference in the constructor
 * for the derived class, this fixes the choice of logger for the duration
 * of the Bank object. Recall, references can't be reseated, so if this is 
 * desireable, then use this method. 
 */
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

