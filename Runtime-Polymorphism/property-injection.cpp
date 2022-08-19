/* property-injection.cpp - exmaple of using property injection 
 * for the interface. */
#include <iostream>
#include <stdexcept>

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

/* Property injection - allows you to change the behavior of 
 * the class by using a pointer which can be reseated instead
 * of using a reference.
 * A good practice is to check to make sure that the property 
 * injected interface is not null before attempting to use it.
 */

struct Bank 
{
	void set_logger(Logger* new_logger)    // use method to set logger manually
	{
		logger = new_logger;
	}
	void make_transfer(long from, long to, double amount)
	{
		if (logger == nullptr)
			throw std::runtime_error{"Error, accessing null"};
		// Notionally transfer funds
		logger->log_transfer(from, to, amount);    // use arrow, not dot
	}
	private:
		Logger* logger{};    // field must now be a pointer
};

int main()
{
	// create both types of loggers to allow for switching as needed
	ConsoleLogger console_logger;
	FileLogger file_logger;

	Bank bank;    // no need for a constructor with property injection
	bank.set_logger(&console_logger);   // method using reference to logger type
	try
	{
	bank.make_transfer(1000, 2000, 49.95);    // console logging
	bank.set_logger(&file_logger);
	bank.make_transfer(2000, 40000, 20.00);    // file logging
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

