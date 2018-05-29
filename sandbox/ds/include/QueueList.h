#pragma once

#include "SinglyLinkedList.h"
#include <stdint.h>

template <typename T>
class QueueList
{
public:
	void add(const T& val)
	{
		_list.push_front(val);
	}

	void remove()
	{
		_list.pop_back();
	}

	void print()
	{
		_list.print();
	}

	void reverse()
	{
		_list.reverse();
	}

	T& front()
	{
		return _list.tail()->val;
	}

	int32_t size()
	{
		return _list.size();
	}

private:

	SinglyLinkedList<T> _list;
};
