#include <iostream>
#include <vector>
#include <set>
#include <windows.h>

#include "WinTimer.h"

using std::cout;
using std::endl;
using std::vector;
using std::set;

typedef int64_t test_t;

void fillVector(vector<test_t>& testVec, int vecSize)
{
	for (int i = 0; i < vecSize; i++)
	{
		testVec.push_back(static_cast<test_t>(i));
	}
}

void fillSet(set<test_t>& testSet, int setSize)
{
	for (int i = 0; i < setSize; i++)
	{
		testSet.insert(static_cast<test_t>(i));
	}
}

test_t iterateVector(vector<test_t>& testVec)
{
	test_t sum = 0;

	for (vector<test_t>::iterator it = testVec.begin(); it != testVec.end(); ++it)
	{
		sum += *it;
	}

	return sum;
}

test_t iterateSet(set<test_t>& testSet)
{
	test_t sum = 0;

	for (set<test_t>::iterator it = testSet.begin(); it != testSet.end(); ++it)
	{
		sum += *it;
	}

	return sum;
}

void benchVector(int size)
{
	vector<test_t> testVec;

	WinTimer timer(1000.0); // ms
	fillVector(testVec, size);
	cout << "Vector fill, " << size << " elements: " << timer.TimeElapsed() << "ms" << endl;

	timer.RestartTimer();
	int64_t sum = iterateVector(testVec);
	cout << "Vector itereate, " << size << " elements: " << timer.TimeElapsed() << "ms (test sum = " << sum << ")" << endl;

	return;
}

void benchSet(int size)
{
	set<test_t> testSet;

	WinTimer timer(1000.0); // ms
	fillSet(testSet, size);
	cout << "Set fill, " << size << " elements: " << timer.TimeElapsed() << "ms" << endl;

	timer.RestartTimer(); 
	int64_t sum = iterateSet(testSet);
	cout << "Set itereate, " << size << " elements: " << timer.TimeElapsed() << "ms (test sum = " << sum << ")" << endl;

	return;
}

int main()
{
	for (int size = 100, i = 1; size <= 10000000; size *= 10, i++)
	{
		cout << "Test " << i << endl;
		benchVector(size);
		benchSet(size);
		cout << endl;
	}

	return 0;
}