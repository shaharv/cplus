#include "../include/DoublyLinkedList.h"

#include <iostream>
#include <stdint.h>

using std::cout;
using std::endl;

int main()
{
	DoublyLinkedList<int32_t> list;

	// insert test
	cout << "Insertion test:" << endl;
	list.insert(1);
	list.insert(11);
	list.insert(111);
	list.insert(1111);
	list.insert(11111);
	list.insert(111111);
	list.print();
	cout <<"Test case end." << endl << endl;

	// list copy + desruction test
	cout << "Copy test:" << endl;
	{
	        DoublyLinkedList<int32_t> list2(list);
		list2.print();
	}
	list.print();
	cout <<"Test case end." << endl << endl;

	// assignment test
	DoublyLinkedList<int32_t> list3(list);
	cout << "Assignment test:" << endl;
	list.remove(list.tail());
	list.remove(list.tail());
	list3 = list;
	list3.print();
	list.print();
	cout <<"Test case end." << endl << endl;

	// reversal test
	cout << "Reversal test #1:" << endl;
	list3.reverse();
	list3.print();
	cout <<"Test case end." << endl << endl;

	// reversal test
	cout << "Reversal test #2:" << endl;
	cout << "Original list:" << endl;
	list3.print();
	cout << "Insert 55 to end..." << endl;
	list3.insert(55);
	cout << "Reversed:" << endl;
	list3.reverse();
	list3.print();
	cout <<"Test case end." << endl << endl;

	// remove test
	cout << "Remove test:" << endl;
	list.remove(list.tail());
	list.remove(NULL);
	list.print();
	list.remove(list.head());
	list.remove(list.tail());
	list.print();
	list.remove(list.tail());
	list.remove(list.head());
	list.remove(list.head());
	list.remove(list.head());
	list.print();
	cout <<"Test case end." << endl << endl;

	return 0;
}
