/* Implement a copy constructor for SimpleString 
 * as well as a copy assignment operator */
#include <iostream>
#include <stdexcept>
#include <cstdio>

/* TODO: Implement move constructor and assignment for SimpleString */

struct SimpleString 
{
	SimpleString(size_t max_size)
		: max_size{max_size}, length{}
	{
		if (max_size == 0)    // catch error in constructor, at least length for null byte
		{
			throw std::runtime_error{"Max size must be at least 1."};
		}
		buffer = new char[max_size];    // point to newly allocated char array
		buffer[0] = 0;    // set first character to 0 since string is initially empty 
	}
	SimpleString(const SimpleString& other)    // copy constructor
		: max_size{other.max_size}, buffer{new char[other.max_size]}, length{other.length}
	{
		/* do a deep copy by allocating on free store and copy all buffer contents */
		std::strncpy(buffer, other.buffer, max_size);
	}
	SimpleString& operator=(const SimpleString& other)    // copy assignment operator
	{
		if (this == &other)    // check if these are the same object
			return *this;

		// free other's current resources and values 
		const auto new_buffer = new char[other.max_size];    // allocate on free store
		delete[] buffer;    // delete this objects reference to free store
		buffer = new_buffer;    // set buffer to newly allocated free store
		length = other.length;    // copy length 
		max_size = other.max_size;    // copy max_size
		std::strncpy(buffer, other.buffer, max_size);    // deep copy buffer contents
		return *this;    // return a reference to the result
	}
	~SimpleString()
	{
		delete[] buffer;
	}
	void print(const char* tag) const    // takes constant pointer to char; won't modify object state (const)
	{
		printf("%s: %s", tag, buffer);    // print tag and whatever is in the buffer
						  // notice the buffer will move along until it is reset
	}
	// review this method to make sure you understand it better
	bool append_line(const char* x)
	{
		/* takes a null-terminated string and adds its contents to buffer */
		const auto x_len = strlen(x);    // get lenth of x
		if (x_len + this->length + 2 > max_size)    // exceed max? (including null and newline)
			return false;    // not enough space
		std::strncpy(buffer + length, x, max_size - length);   // copy bytes of x into buffer
		this->length += x_len;    // adjust length of char array
		this->buffer[length++] = '\n';     // increment buffer size by one to add newline
		this->buffer[length] = 0;    // add null terminator after newline
		return true;
	}
	private:
		size_t max_size{};    // max length of string including null terminator
		char* buffer{};
		size_t length{};
};

/* Define a class with a SimpleString member */
struct SimpleStringOwner
{
	SimpleStringOwner(const char* x)
		: string{10}
	{
		// construct a string object
		if(!string.append_line(x))    
			throw std::runtime_error{"Not enough memory!"};
		string.print("\nConstructed");    
	}
	~SimpleStringOwner()
	{
		string.print("About to destroy");
	}
	private:
		SimpleString string;
};

int main()
{
	/* copy constructor */
	SimpleString a{50};
	a.append_line("We apologize for the");
	
	SimpleString a_copy{a};   
	a.append_line("incovenience.");
	a_copy.append_line("incontinence.");
	
	a.print("a");
	a_copy.print("a_copy");

	/* copy assignment */ 
	SimpleString b{50};
	b.append_line("Last message.");

	a.print("a");
	b.print("b");

	b = a; 
	a.print("a");
	b.print("b");
}
