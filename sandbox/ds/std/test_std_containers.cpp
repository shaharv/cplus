#include <list>
#include <iostream>
#include <stack>
#include <stdint.h>

void test_stack()
{
	const std::string strArr[] = { "it", "rained", "in", "southern", "spain", "man" };
	const int32_t strCount = sizeof(strArr) / sizeof(strArr[0]);

	std::stack<std::string, std::list<std::string> > strings;

	std::cout << "Populating the stack:" << std::endl;

	for (int32_t i = 0; i < strCount; i++)
	{
		strings.push(strArr[i]);
		std::cout << strArr[i] << std::endl;
	}

	std::cout << std::endl << "Popping the stack:" << std::endl;

	while (!strings.empty())
	{
		std::cout << strings.top() << std::endl;
		strings.pop();
	}
}

int main()
{
	test_stack();
	return 0;
}
