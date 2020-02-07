#include <iostream>
#include <stdint.h>

using std::cerr;
using std::cout;
using std::endl;
using std::swap;

template <typename T> void printSubsets(T arr[], int32_t size);
template <typename T> void printSubset(T arr[], int32_t bitmask, int32_t numOfBits);
template <typename T> void printPermutations(T arr[], int32_t size);
template <typename T> void printPermutationsHelper(T arr[], int32_t size, int32_t left, int32_t right);
template <typename T> void printArr(T arr[], int32_t size);

template <typename T>
void printSubsets(T arr[], int32_t size)
{
	if (size > 16)
	{
		cerr << "Size = " << size << "is too big!" << endl;
		cerr << "Printing 2^16 subsets." << endl;
		size = 16;
	}

	for (int32_t i = 0; i < (1 << size); i++)
	{
		printSubset(arr, i, size);
	}
}

template <typename T>
void printSubset(T arr[], int32_t bitmask, int32_t numOfBits)
{
	cout << bitmask << ":  ";

	for (int32_t i = 0; i < numOfBits; i++)
	{
		if ((bitmask & (1 << i)) !=  0)
		{
			cout << " " << arr[i] << " ";
		}
		else
		{
			cout << "   ";
		}
	}

	cout << endl;
}

template <typename T>
void printPermutations(T arr[], int32_t size)
{
	printPermutationsHelper(arr, size, 0, (size - 1));
}

template <typename T>
void printPermutationsHelper(T arr[], int32_t size, int32_t left, int32_t right)
{
	if (left == right)
	{
		printArr(arr, size);
		return;
	}

	for (int32_t i = left; i <= right; i++)
	{
		swap(arr[left], arr[i]);
		printPermutationsHelper(arr, size, (left + 1), right);
		swap(arr[i], arr[left]);
	}
}

template <typename T>
void printArr(T arr[], int32_t size)
{
	for (int32_t i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
}

int main()
{
	int32_t arr1[] = { 1, 2, 3, 4 };
	printSubsets(arr1, (sizeof(arr1) / sizeof(arr1[0])));

	cout << endl;

	printPermutations(arr1, (sizeof(arr1) / sizeof(arr1[0])));

	cout << endl;

	std::string arr2[] = { "a", "b", "c" };
	printSubsets(arr2, (sizeof(arr2) / sizeof(arr2[0])));

	printPermutations(arr2, (sizeof(arr2) / sizeof(arr2[0])));

	return 0;
}
