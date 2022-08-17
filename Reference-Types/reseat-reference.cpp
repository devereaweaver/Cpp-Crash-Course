/* Remember, references CAN'T be reseated */
#include <iostream>
#include <cstdio>

int main()
{
	int original = 100;
	int& original_ref = original;    // reference to original 
	printf("Original: %d\n", original);
	printf("Reference: %d\n", original_ref);

	/* Reassigning a reference value will change the value of
	 * whatever object the reference was originally referencing
	 * when it was created. This will not change.
	 */
	int new_value = 200;
	original_ref = new_value;
	printf("Original: %d\n", original);
	printf("New Value: %d\n", new_value);
	printf("Reference: %d\n", original_ref);    // should print 200
}

