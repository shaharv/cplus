#include <iostream>
#include <stdint.h>

#include "include/StackArray.h"

using std::cout;
using std::endl;

void test_stack();
void reverse_stack(StackArray<int32_t>& stack);

int main()
{
	test_stack();

	return 0;
}

void test_stack()
{
	StackArray<int32_t> s1;

	// Print empty stack
	s1.print();

	s1.push_back(1);
	s1.push_back(2);
	s1.push_back(3);
	s1.push_back(4);
	s1.print();

	reverse_stack(s1);
	cout << "Reversed stack:" << endl;
	s1.print();

	StackArray<int32_t> s2(s1);
	cout << "Copied stack:" << endl;
	s2.print();

	s2.pop_back();
	s2.pop_back();
	s2.push_back(1234);
	cout << "Copied stack, pop-pop-push:" << endl;
	s2.print();

	return;
}

void reverse_stack(StackArray<int32_t>& stack)
{
	StackArray<int32_t> s1, s2;
	int32_t size = stack.size();

	for (int32_t i = 0; i < size; i++)
	{
		int32_t top = stack.top();
		s1.push_back(top);
		stack.pop_back();
	}

	for (int32_t i = 0; i < size; i++)
	{
		int32_t top = s1.top();
		s2.push_back(top);
		s1.pop_back();
	}

	for (int32_t i = 0; i < size; i++)
	{
		int32_t top = s2.top();
		stack.push_back(top);
		s2.pop_back();
	}
}
