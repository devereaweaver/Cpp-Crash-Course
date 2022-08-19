/* bank.cpp - implementation of exercise for end of chapter */
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

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
//------------------------------------------------------------------------

struct AccountDatabase    // interface for rudimentary accounting system
{
	virtual ~AccountDatabase() = default; 
	virtual double retrieveAmount(long id) = 0;
	virtual void setAmount(long id, double amount) = 0;
	virtual void addAccount(double amount) = 0;
};

/* Generate a class that implements AccountDatabase interface */
struct InMemoryAccountDatabase : AccountDatabase
{
	void addAccount(double amount) override
	{
		/* TODO: Check to make sure index isn't already in account */
		/* Notionally check if account already exits for now */
		id = rand() % 99999 + 11111;    // NOT ideal, but works for this scope
		std::cout << "Congratulations! Your ID # is : " << id << std::endl;
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
//------------------------------------------------------------------------

struct Bank 
{
	Bank(Logger* logger, AccountDatabase& ad) 
		: logger{logger}, ad{ad}{};   
	void set_logger(Logger* new_logger)  // property injection - set type of logger
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
	void createAccount()
	{
		double amount{};
		std::cout << "\nThank you for creating an account, " 
			  << "enter amount for initial deposit: ";
		std::cin >> amount;
		ad.addAccount(amount);
	}
	void deposit()
	{
		long id;
		std::cout << "Enter account id to deposit funds: ";
		std::cin >> id;
		double amount;
		std::cout << "Enter amount to deposti: ";
		std::cin >> id;
		ad.setAmount(id, amount);
	}
	void viewBalance()
	{
		long id;
		std::cout << "\nEnter account id to view balance: ";
		std::cin >> id;
		std::cout << "Current balance: $" << ad.retrieveAmount(id) << std::endl;
	}
	private:
		Logger* logger{};  // property injected - mutable after creation 
		AccountDatabase& ad;   // constructioin injected - immutable after creation
};

int main()
{
	/* TODO: Just make this some kind of menu-driven console thing */

	// create instances of a logger and an account database
	ConsoleLogger logger{};
	InMemoryAccountDatabase database{};

	// create instance of Bank class with two instances above
	Bank bank{&logger, database};    // logger must be passed by address for now
	
	// add a few accounts to the Bank database member
	for (auto i{0}; i < 4; ++i)
		bank.createAccount();
	bank.viewBalance();
}

