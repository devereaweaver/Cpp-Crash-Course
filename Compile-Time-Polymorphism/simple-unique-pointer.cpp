/* implementation of a unique pointer to demonstrate 
 * generate programming principles
 */
#include <iostream>
#include <utility>

template<typename T>
struct SimpleUniquePointer 
{
	SimpleUniquePointer() = default;
	SimpleUniquePointer(T* pointer)
		: pointer{pointer}{}
	~SimpleUniquePointer()
	{
		if(pointer) delete pointer;   // check if null
	}
	/* don't use default copy constructor or copy assigment operator */
	/* we only want ONE owner of data, thus we remove the ability to copy */
	SimpleUniquePointer(const SimpleUniquePointer&) = delete;  
	SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;
	SimpleUniquePointer(SimpleUniquePointer&& other) noexcept // mc
		: pointer{other.pointer}
	{
		other.pointer = nullptr;
		// destructor will delete the moved-from object
	}
	SimpleUniquePointer& operator=(SimpleUniquePointer&& other) noexcept
	{
		if (pointer) delete pointer;   // check for prior ownership
		pointer = other.pointer;
		other.pointer = nullptr;
		return *this;
	}
	T* get() {return pointer;}  // get access to pointed to data on free store
	private:
		T* pointer;
};

struct Tracer
{
	Tracer(const char* name) : name{name}
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

void consumer(SimpleUniquePointer<Tracer> consumer_ptr)
{
	std::cout << "(cons) consumer_ptr: " << consumer_ptr.get()
		  << std::endl;
}

int main()
{
	/* create unique pointer by dynamically allocating 
	 * a Tracer object */
	auto ptr_a = SimpleUniquePointer(new Tracer{"ptr_ a"});

	/* get address of pointer to Tracer object */
	std::cout << "(main) ptr_a: " << ptr_a.get() << std::endl;
	
	/* relinquish Tracer of ptr_a to consumer function which 
	 * moves ptr_a into the consumer_ptr argument */
	consumer(std::move(ptr_a));    // ptr_a gets destroyed

	/* show that ptr_a is now null */
	std::cout << "(main): ptr_a: " << ptr_a.get() << std::endl;
}

