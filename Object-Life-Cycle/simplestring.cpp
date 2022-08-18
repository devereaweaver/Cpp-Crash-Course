/* simplestring.cpp - from C++ Crash Coures, an example of using constructors,
 * destructors, members, and exceptions
 */
#include <iostream>
#include <stdexcept>
#include <cstdio>

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
	~SimpleString()
	{
		delete[] buffer;
	}
	void print(const char* tag) const    // takes constant pointer to char; won't modify object state (const)
	{
		printf("%s: %s", tag, buffer);    // print tag and whatever is in the buffer
						  // notice the buffer will move along until it is reset
	}
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

struct SimpleStringOwner
{
	SimpleStringOwner(const char* x)
		: string{10}
	{
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
	SimpleString string{115};     

	// let's add some contents to the buffer
	string.append_line("Starbuck, whaddya hear?");
	string.append_line("Nothin' but the rain.");
	string.print("A");    // print out tag and buffer contents
	
	// let's add more contents to the buffer
	string.append_line("Grab your gun and bring the cat in.");
	string.append_line("Aye-aye sir, coming home.");
	string.print("B");    // print tag and buffer

	// try to add a little more to the buffer, but likely won't work
	if(!string.append_line("Galatica!"))
		printf("\nString was not big enough to append another message.");

	// test out SimpleStringOwner
	SimpleStringOwner x{"x"};
	printf("\nx is alive.\n");
}
