#pragma once

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <iostream>

template <typename T>
class StackArray
{
private:
	static const int32_t INITIAL_CAPACITY = 64;

public:
	StackArray()
	{
		_capacity = INITIAL_CAPACITY;
		_arr = new T[_capacity];
		_size = 0;
	}

	StackArray(int32_t capacity)
	{
		_capacity = capacity;
		_arr = new T[capacity];
		_size = 0;
	}

	~StackArray()
	{
		delete[] _arr;
	}

	StackArray(const StackArray& stack)
	{
		_capacity = stack._capacity;
		_size = stack._size;
		_arr = new T[_capacity];
		memcpy(_arr, stack._arr, static_cast<size_t>(_size) * sizeof(T&));
	}

	StackArray& operator=(StackArray stack)
	{
		swap(*this, stack);
		return *this;
	}

	void push_back(const T& val)
	{
		if (_size >= _capacity)
		{
			T* newArr = new T[_capacity * 2];
			T* oldArr = _arr;
			memcpy(newArr, _arr, static_cast<size_t>(_size) * sizeof(T&));
			_arr = newArr;
			delete[] oldArr;
		}

		_size++;
		_arr[_size - 1] = val;
	}

	void pop_back()
	{
		if (_size == 0)
		{
			return;
		}

		_size--;
	}

	void print()
	{
		if (_size == 0)
		{
			std::cout << "[Stack is empty]" << std::endl;
			return;
		}

		std::cout << _arr[_size - 1] << " <- top" << std::endl;

		if (_size == 1)
		{
			return;
		}

		for (int32_t i = _size - 2; i >= 0; i--)
		{
			std::cout << _arr[i] << std::endl;
		}
	}

	T& top()
	{
		assert((_size > 0) && ("top() called on empty stack!"));
		return _arr[_size - 1];
	}

	int32_t size()
	{
		return _size;
	}

private:
	void swap(StackArray& a, StackArray& b)
	{
		using std::swap;

		swap(a._arr, b._arr);
		swap(a._size, b._size);
		swap(a._capacity, b._capacity);
	}

	T* _arr;
	int32_t _capacity;
	int32_t _size;
};
