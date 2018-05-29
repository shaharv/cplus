#pragma once

#include <assert.h>
#include <iostream>
#include <stdint.h>

template <typename T>
class SinglyLinkedList
{
private:
	class Node
	{
	public:
		Node(T val) : _next(NULL), _val(val)
		{
		}

		~Node()
		{
		}

	private:
		Node(const Node&);
		const Node& operator=(const Node&);

		Node* _next;
		T _val;

		friend class SinglyLinkedList;
	};

public:
	SinglyLinkedList() : _head(NULL), _tail(NULL), _size(0)
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list) : _head(NULL), _tail(NULL), _size(0)
	{
		Node* currNode = list._head;

		while(currNode != NULL)
		{
			push_back(currNode->_val);
			currNode = currNode->_next;
		}

		assert(_size == list._size);
	}

	const SinglyLinkedList& operator=(SinglyLinkedList list)
	{
		swap(*this, list);
		return *this;
	}

	~SinglyLinkedList()
	{
		if (_head == NULL)
		{
			return;
		}

		Node* nextNode = _head->_next;
		delete _head;

		while (nextNode != NULL)
		{
			Node* currNode = nextNode;
			nextNode = nextNode->_next;
			delete currNode;
		}
	}

	Node* head()
	{
		return _head;
	}

	Node* tail()
	{
		return _tail;
	}

	int32_t size()
	{
		return _size;
	}

	void push_back(const T& val)
	{
		if (_head == NULL)
		{
			push_first_node(val);
			return;
		}

		Node* newTail = new Node(val);
		newTail->_next = NULL;
		newTail->_val = val;
		_tail->_next = newTail;
		_tail = newTail;
		_size++;
	}

	void push_front(const T& val)
	{
		if (_head == NULL)
		{
			push_first_node(val);
			return;
		}

		Node* newHead = new Node(val);
		newHead->_next = _head;
		newHead->_val = val;
		_head = newHead;
		_size++;
	}

	void pop_back()
	{
		if (_size == 0)
		{
			return;
		}

		if (_size == 1)
		{
			_head = _tail = NULL;
			_size = 0;
			return;
		}

		Node* node = _head;
		Node* prev = node;

		while ((node != NULL) && (node != _tail))
		{
			prev = node;
			node = node->_next;
		}

		prev->_next = NULL;
		_tail = prev;
		_size--;
	}

	void remove(const T& val)
	{
		if (_size == 0)
		{
			return;
		}

		if (_head->_val == val)
		{
			if (_head == _tail)
			{
				_tail = _head = NULL;
				_size = 0;
				return;
			}

			Node* oldHead = _head;
			_head = _head->_next;
			delete oldHead;
			_size--;
			return;
		}

		Node* node = _head;
		Node* prev = node;

		while ((node != NULL) && (node->_val != val))
		{
			prev = node;
			node = node->_next;
		}

		if (node == NULL)
		{
			return;
		}

		if (node == _tail)
		{
			Node* oldTail = _tail;
			prev->_next = NULL;
			_tail = prev;
			delete oldTail;
			_size--;
			return;
		}

		prev->_next = node->_next;
		delete node;
		_size--;
	}

	void reverse()
	{
		if (_size < 2)
		{
			return;
		}

		assert((_head != NULL) && (_tail != NULL));

		Node* node = _head;
		Node* prev = NULL;

		Node* oldTail = _tail;
		_tail = _head;
		_head = oldTail;

		while (node != NULL)
		{
			Node* next = node->_next;
			node->_next = prev;
			prev = node;
			node = next;
		}
	}

	void print()
	{
		std::cout << "List size = " << _size << std::endl;

		if (_head == NULL)
		{
			return;
		}

		std::cout << _head->_val << " -> ";
		Node* nextNode = _head->_next;

		while (nextNode != NULL)
		{
			std::cout << nextNode->_val << " -> ";
			nextNode = nextNode->_next;
		}

		std::cout << "end" << std::endl;
	}

private:
	void push_first_node(const T& val)
	{
		assert((_head == NULL) && (_tail == NULL) && (_size == 0));
		_head = new Node(val);
		_tail = _head;
		_size++;
	}

	void swap(SinglyLinkedList& listA, SinglyLinkedList& listB)
	{
		using std::swap;

		swap(listA._head, listB._head);
		swap(listA._tail, listB._tail);
		swap(listA._size, listB._size);
	}

	Node* _head;
	Node* _tail;
	int32_t _size;
};
