/* Attempt at making a doubly liked list */
#include <iostream>

struct Element
{
	Element(char f, char l,  short operating_number):
		operating_number{operating_number}
	{
		prefix[0] = f;
		prefix[1] = l;
	}
	Element* next{};    // pointer to next Element in list
	Element* previous{};    // pointer to previous Element in list
	void insert_after(Element* new_element)
	{
		if(this->next != nullptr)
			this->next->previous = new_element;
		new_element->next = this->next;   // set next member of new element to the next of this 
		new_element->previous = this;
		next = new_element;    // set this next to point to new element
	} 
	void insert_before(Element* new_element)
	{
		this->previous->next = new_element;
		new_element->next = this;
		new_element->previous = this->previous;
		this->previous = new_element;
	}
	char prefix[2];    
	short operating_number;
};

int main()
{
	Element trooper1('T', 'K', 421);
	Element trooper2('F', 'N', 2187);
	Element trooper3('L', 'S', 005);
	Element trooper4('D', 'W', 6969);
	Element trooper5('D', 'B', 312);

	// start linked list 
	trooper1.insert_after(&trooper2);   
	trooper2.insert_after(&trooper3);
	trooper3.insert_after(&trooper5);    // the insert after works 

	// let's insert trooper4 before trooper2
	trooper2.insert_before(&trooper4);

	
	/* Use pointer to trooper1 to traverse the linked list and print out members */
	/* The second statement makes sure the cursor pointer is not null */
	std::cout << "Forward traversal:" << std::endl;
	for(Element* cursor = &trooper1; cursor; cursor = cursor->next)
		std::cout << cursor->prefix[0] << cursor->prefix[1] << "-" << cursor->operating_number << std::endl;

	std::cout << "\nReverse traversal: " << std::endl;
	for(Element* cursor = &trooper5; cursor; cursor = cursor->previous)
		std::cout << cursor->prefix[0] << cursor->prefix[1] << "-" << cursor->operating_number << std::endl;

}

