/* From C++ Crash Course - example of a Tracer class
 * that keeps track of the different types of object
 * life cycles.
 */
#include<iostream>

struct Tracer
{ 
	Tracer(const char* name): name{name}
	{
		std::cout << name << " constructed." << std::endl;
	}
	~Tracer()
	{
		std::cout << name << " destructed." << std::endl;
	}
	private:
		const char* const name;
};

static Tracer t1{"Static variable"};    // static duration (start/end of program)
thread_local Tracer t2{"Thread-local variable"};    // thread local 

int main()
{
	const auto t2_ptr = &t2;    // pointer to thread_local variable 
	Tracer t3{"Automatic variable"};    // automatic storage duration (end of main)
	const auto* t4 = new Tracer{"Dynamic variable"};    // allocated variable (until delete)
	delete t4;
}


