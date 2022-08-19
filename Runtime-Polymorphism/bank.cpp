/* bank.cpp - implementation of exercise for end of chapter */
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

struct Logger    
{
	virtual ~Logger() = default;   
	virtual void log_transfer(long from, long to, double amount) = 0; 
};

struct ConsoleLogger : Logger    
{
	void log_transfer(long from, long to, double amount) override
	{
		std::cout << "[console] " << from << " -> " << to << ": " 
		 	  << amount << std::endl;
	}
};

struct FileLogger : Logger     
{
	void log_transfer(long from, long to, double amount) override
	{
		std::cout << "[file] " << from << " -> " << to << ": " 
		 	  << amount << std::endl;
	}
};

struct AccountDatabase    // interface for rudimentary accounting system
{
	virtual ~AccountDatabase() = default; 
	virtual double retrieveAmount(long id) = 0;
	virtual void setAmount(long id, double amount) = 0;
};

/* Generate a class that implements AccountDatabase interface */
struct InMemoryAccountDatabase : AccountDatabase
{
	void addAccount(long id, double amount)
	{
		/* TODO: Check to make sure index isn't already in account */
		/* Notionally check if account already exits for now */
		ids.push_back(id);
		amounts.push_back(amount);
	}
	double retrieveAmount(long id) override
	{
		/* TODO: Implement logic if account id isn't found */
		/* Notially check if account isn't found */
		double amount{};
		for (auto i{0}; i < ids.size(); ++i)
		{
			if (id == ids[i])
				amount = amounts[i];
			/* Return logic here for non-existing ID */
		}
		return amount;
	}
	void setAmount(long id, double amount) override
	{
		for (auto i{0}; i < ids.size(); ++i)
			if (id == ids[i])
			{
				amounts[i] += amount;
				std::cout << "\n$" << amount << " deposited to account " << id << "." << std::endl;
			}
	}

	private:
		long id{};
		std::vector<long> ids{};
		std::vector<double> amounts{};
};

struct Bank 
{
	Bank(Logger* logger) : logger{logger}{};   // construction injection
	void set_logger(Logger* new_logger)        // property injection
	{
		logger = new_logger;
	}
	void make_transfer(long from, long to, double amount)
	{
		if (logger == nullptr)
			throw std::runtime_error{"Error, accessing null"};
		// Notionally transfer funds
		logger->log_transfer(from, to, amount);    
	}
	private:
		Logger* logger{};    
};

int main()
{
	InMemoryAccountDatabase db;
	db.addAccount(11111, 50.50);
	db.addAccount(22222, 100.96);
	db.addAccount(33333, 20.00);
	db.addAccount(44444, 0.81);

	bool flag{true};
	while(flag)    // rudimentary testing, change later after learning about testing frameworks
	{
		long id{};
		std::string c{};
		std::cout << "Enter account ID: ";
		std::cin >> id;
		std::cout << "Account # " << id << ":\nBalance: " << db.retrieveAmount(id) << std::endl;
		db.setAmount(id, 500.);  // test setting amount
		std::cout << "\nAccount # " << id << ":\nBalance: " << db.retrieveAmount(id) << std::endl;
		std::cout << "\nContinue? [y/N] > ";
		std::cin >> c;
		if (c == "y")
			flag = true;
		else
			flag = false;
	}
}

