#include "include/SinglyLinkedList.h"

#include <iostream>
#include <stdint.h>

using std::cout;
using std::endl;

int main()
{
	SinglyLinkedList<int32_t> list;

	// push_back test
	cout << "push_back test:" << endl;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);
	list.print();
	cout <<"Test case end." << endl << endl;

	// list copy + desruction test
	cout << "Copy test:" << endl;
	{
		SinglyLinkedList<int32_t> list2(list);
		list2.print();
	}
	list.print();
	cout <<"Test case end." << endl << endl;

	// reversal test
	cout << "Reversal test #1:" << endl;
	list.reverse();
	list.print();
	cout <<"Test case end." << endl << endl;

	// assignment test
	SinglyLinkedList<int32_t> list3(list);
	cout << "Assignment test:" << endl;
	cout << "Removing 2, 3..." << endl;
	list.remove(2);
	list.remove(3);
	list3 = list;
	list3.print();
	list.print();
	cout <<"Test case end." << endl << endl;

	// reversal test
	cout << "Reversal test #2:" << endl;
	cout << "Original list:" << endl;
	list3.print();
	cout << "push_back 55 to end..." << endl;
	list3.push_back(55);
	cout << "Reversed:" << endl;
	list3.reverse();
	list3.print();
	cout << "Test case end." << endl << endl;

	// remove test
	cout << "Remove test:" << endl;
	list.remove(6);
	list.remove(0);
	list.print();
	cout << "Removing 1, 3, 3..." << endl;
	list.remove(1);
	list.remove(3);
	list.remove(3);
	list.print();
	cout << "Removing 4, 4, 5..." << endl;
	list.remove(4);
	list.remove(4);
	list.remove(5);
	list.print();
	cout <<"Test case end." << endl << endl;

	// push_front test
	cout << "push_front test:" << endl;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	list.push_front(5);
	list.push_front(6);
	list.print();
	cout <<"Test case end." << endl << endl;

	return 0;
}
