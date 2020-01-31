#include <iostream>
#include <stdint.h>

#include "../include/QueueList.h"

using std::cout;
using std::endl;

void test_Queue();

int main()
{
	test_Queue();

	return 0;
}

void test_Queue()
{
	QueueList<int32_t> q1;

	// Print empty Queue
	q1.print();

	q1.add(1);
	q1.add(2);
	q1.add(3);
	q1.add(4);
	q1.print();

	q1.reverse();
	cout << "Reversed Queue:" << endl;
	q1.print();

	QueueList<int32_t> q2(q1);
	cout << "Copied Queue:" << endl;
	q2.print();

	q2.remove();
	q2.remove();
	q2.add(1234);
	cout << "Copied Queue, pop-pop-push:" << endl;
	q2.print();

	return;
}
