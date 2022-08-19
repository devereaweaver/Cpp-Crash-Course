/* timerclass.cpp - an implementation of a TimerClass
 * to practice with the ideas of object life cycle 
 * in C++. 
 *
 * By: Devere Anthony Weaver 
 */
#include <iostream>
#include <sys/time.h>
#include <string>

struct TimerClass
{
	TimerClass(std::string name)
		: name(name)
	{
		std::cout << name << " timer created." << std::endl;
		gettimeofday(&timestamp, NULL);   
	}
	TimerClass(std::string name, const TimerClass& other)    // cc
		: name(name), timestamp(other.timestamp){}
	TimerClass& operator=(const TimerClass& other)    // ca
	{
		if (this == &other)
			return *this;
		timestamp = other.timestamp;
		return *this;
	}
	TimerClass(std::string name, TimerClass&& t )    // mc
		: name(name), timestamp(t.timestamp)
	{
		t.moved_from = true;    // don't make argument const bc we need to update it
	}    
	TimerClass& operator=(TimerClass&& src)    // ma
	{
		// steal data
		this->timestamp = src.timestamp;
		this->name = src.name;
		src.timestamp = (struct timeval){0};    // zero out source timestamp
		src.name.clear();    // clear source name
		src.moved_from = true;
		return *this;
	}
	~TimerClass()
	{
		timeval destructTime{}, lifetime{};
		gettimeofday(&destructTime, NULL);
		timersub(&timestamp, &destructTime, &lifetime); // rough lifetime
		if (!moved_from)
			std::cout << name << " rough lifetime: " << lifetime.tv_usec << " ms." << std::endl;
	}
	private:
		timeval timestamp{};
		std::string name{};
		bool moved_from{false};    // keep track of it the object has been moved from
};

void shortTimer(std::string s)    //let TimerClass go out of scope for demonstration
{
	TimerClass t{s};
}

int main()
{
	/* Demonstrate the different constructors/assignments */
	TimerClass l{"Longer"};    // lifetime is main
	shortTimer("Short");
	int x{1};

	for (auto i{0}; i < 10000; ++i)    // show liftime is longer
	{
		x += x;
	}

	// test copy constructor
	TimerClass copied{"Copied", l};    // should always be longer than l

	// test copy assignment
	TimerClass copyAssigned{"CopyAssigned"};
	copyAssigned = copied;    // should now have the longest timestamp

	// test move constructor
	// a move costructor here doesn't make the most sense
	// but it is here for demonstration/practice purposes
	TimerClass moveConstructed{"MoveConstructed", TimerClass{"moved"}};

	// test move assignment operator
	TimerClass moveAssigned = TimerClass{"moveAssigned"};

	std::cout << "\nCleaning up main.\n" << std::endl;
}
