#include <list>
#include <iostream>
#include <queue>
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

	std::cout << std::endl;
}

void test_priority_queue()
{
	const int32_t intArr[] = { 4, -1, 10, 4, 7, 8, 5, 1, 3, 2, 0, 9, 6 };
	const int32_t intArrSize =  sizeof(intArr) / sizeof(intArr[0]);

	std::priority_queue<int32_t, std::vector<int32_t> > intQueue;

	std::cout << "Pushing elements to priority queue (heap):" << std::endl;

	for (int32_t i = 0; i < intArrSize; i++)
	{
		intQueue.push(intArr[i]);
		std::cout << intArr[i] << std::endl;
	}

	std::cout << std::endl << "Popping elements from priority queue (heap):" << std::endl;

	while (!intQueue.empty())
	{
		std::cout << intQueue.top() << std::endl;
		intQueue.pop();
	}

	std::cout << std::endl;
}

void test_queue()
{
	const std::string strArr[] = { "Yael", "Guy", "Galit", "Shahar" };

	std::queue<std::string, std::deque<std::string> > strQueue;

	// Use vector, just for fun
	const std::vector<std::string> strVec(strArr, strArr + (sizeof(strArr) / sizeof(strArr[0])));
	std::cout << "Eneueue strings:" << std::endl;
	for (std::vector<std::string>::const_iterator it = strVec.begin(); it != strVec.end(); ++it)
	{
		const std::string& str = *it;
		strQueue.push(str);
		std::cout << str << std::endl;
	}

	std::cout << std::endl << "Dequeue strings:" << std::endl;

	while (!strQueue.empty())
	{
		std::cout << strQueue.front() << std::endl;
		strQueue.pop();
	}

	std::cout << std::endl;
}

template <typename Type, typename VecType, typename ContainerType>
void test_queue(const VecType& vec)
{
	std::queue<Type, ContainerType> queue;

	std::cout << "Enqueue values:" << std::endl;

	for (typename VecType::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		const Type& val = *it;
		queue.push(val);
		std::cout << val << std::endl;
	}

	std::cout << std::endl << "Dequeue values:" << std::endl;

	while (!queue.empty())
	{
		std::cout << queue.front() << std::endl;
		queue.pop();
	}

	std::cout << std::endl;
}

int main()
{
	test_stack();
	test_priority_queue();
	test_queue();

	{
		const std::string strArr[] = { "Yael", "Guy", "Galit", "Shahar", "1", "2" };
		const std::vector<std::string> strVec(strArr, strArr + (sizeof(strArr) / sizeof(strArr[0])));
		test_queue<std::string, std::vector<std::string>, std::deque<std::string> >(strVec);
	}

	return 0;
}
