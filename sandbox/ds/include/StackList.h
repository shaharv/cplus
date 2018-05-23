#pragma once

#include "DoublyLinkedList.h"
#include <stdint.h>

template <typename T>
class StackList
{
public:
	void push_back(const T& val)
	{
		_list.insert(val);
	}

	void pop_back()
	{
		_list.remove(_list.tail());
	}

	void print()
	{
		_list.print();
	}

	void reverse()
	{
		_list.reverse();
	}

	T& top()
	{
		return _list.tail()->val;
	}

	int32_t size()
	{
		return _list.size();
	}

private:

	DoublyLinkedList<T> _list;
};
