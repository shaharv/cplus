#include <iostream>
#include <stdint.h>

#include "include/StackList.h"

using std::cout;
using std::endl;

void test_stack();
void reverse_stack(StackList<int32_t>& stack);

int main()
{
	test_stack();

	return 0;
}

void test_stack()
{
	StackList<int32_t> s1;

	// Print empty stack
	s1.print();

	s1.push_back(1);
	s1.push_back(2);
	s1.push_back(3);
	s1.push_back(4);
	s1.print();

	s1.reverse();
	cout << "Reversed stack:" << endl;
	s1.print();

	StackList<int32_t> s2(s1);
	cout << "Copied stack:" << endl;
	s2.print();

	s2.pop_back();
	s2.pop_back();
	s2.push_back(1234);
	cout << "Copied stack, pop-pop-push:" << endl;
	s2.print();

	return;
}
