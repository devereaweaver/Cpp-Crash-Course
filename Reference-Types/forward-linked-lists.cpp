/* Example implementation of a forward linked list */
/* Traverse a linked list of stormtroopers */ 
#include <iostream>
#include <cstdio>

struct Element
{
	Element* next{};    // pointer to next Element in list
	
	void insert_after(Element* new_element)
	{
		// this isn't necessary, just here for disambiguation
		new_element->next = this->next;   // set next member of new element to the next of this 
		next = new_element;    // set this next to point to new element
	} 
	char prefix[2];    
	short operating_number;
};

int main()
{
	Element trooper1, trooper2, trooper3;    // create three instances of Element
	trooper1.prefix[0] = 'T';
	trooper1.prefix[1] = 'K';
	trooper1.operating_number = 421;

	// start linked list 
	trooper1.insert_after(&trooper2);    // insert trooper2 after trooper1 in liked list
	trooper2.prefix[0] = 'F';
	trooper2.prefix[1] = 'N';
	trooper2.operating_number = 2187;
	trooper2.insert_after(&trooper3);
	trooper3.prefix[0] = 'L';
	trooper3.prefix[1] = 'S';
	trooper3.operating_number = 005;

	/* So now, linked list should start with 1 -> 2 -> 3 */
	
	/* Use pointer to trooper1 to traverse the linked list and print out members */
	/* The second statement makes sure the cursor pointer is not null */
	for(Element* cursor = &trooper1; cursor; cursor = cursor->next)
		std::cout << cursor->prefix[0] << cursor->prefix[1] << "-" << cursor->operating_number << std::endl;

}

