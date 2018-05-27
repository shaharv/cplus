#pragma once

#include <assert.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

template <typename T>
class DoublyLinkedList
{
private:
	class Node
	{
	public:
		Node(T val) : _prev(NULL), _next(NULL), _val(val)
		{
		}

		~Node()
		{
		}

	private:
		Node(const Node&);
		const Node& operator=(const Node&);

		Node* _prev;
		Node* _next;
		T _val;

		friend class DoublyLinkedList;
	};

public:
	DoublyLinkedList() : _head(NULL), _tail(NULL), _size(0)
	{
	}

	DoublyLinkedList(const DoublyLinkedList& list) : _head(NULL), _tail(NULL), _size(0)
	{
		Node* currNode = list._head;

		while(currNode != NULL)
		{
			insert(currNode->_val);
			currNode = currNode->_next;
		}

		assert(_size == list._size);
	}

	const DoublyLinkedList& operator=(DoublyLinkedList list)
	{
		swap(*this, list);
		return *this;
	}

	~DoublyLinkedList()
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

	Node* insert(T val)
	{
		if (_head == NULL)
		{
			assert((_tail == NULL) && (_size == 0));
			_head = new Node(val);
			_tail = _head;
			_size++;
			return _tail;
		}

		Node* newTail = new Node(val);
		newTail->_prev = _tail;
		newTail->_next = NULL;
		newTail->_val = val;
		_tail->_next = newTail;
		_tail = newTail;
		_size++;

		return _tail;
	}

	void remove(Node* node)
	{
		if (node == NULL)
		{
			return;
		}

		Node* nextNode = node->_next;
		Node* prevNode = node->_prev;

		// consistency checks
		assert((node == _head) ? (node->_prev == NULL) : true);
		assert((node == _tail) ? (node->_next == NULL) : true);
		assert(((node == _head) && (node == _tail)) ? (_size == 1) : true);

		if (node != _head)
		{
			node->_prev->_next = nextNode;
		}
		else
		{
			_head = nextNode;
		}

		if (node != _tail)
		{
			node->_next->_prev = prevNode;
		}
		else
		{
			_tail = prevNode;
		}

		delete node;
		_size--;
	}

	void reverse()
	{
		if (_size == 0)
		{
			return;
		}

		assert((_head != NULL) && (_tail != NULL));

		Node* origTail = _tail;
		Node* origHead = _head;
		Node* revIter  = origTail;
		Node* lastIter = NULL;

		while (revIter != NULL)
		{
			Node* prev = revIter->_prev;

			revIter->_next = prev;
			revIter->_prev = lastIter;

			lastIter = revIter;
			revIter = prev;
		}

		_head = origTail;
		_head->_prev = NULL;
		_tail = origHead;
		_tail->_next = NULL;
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
	void swap(DoublyLinkedList& listA, DoublyLinkedList& listB)
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
