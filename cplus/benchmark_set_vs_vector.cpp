#include <iostream>
#include <vector>
#include <set>

#ifdef _WIN32
#include <windows.h>
#include "WinTimer.h"
#define SNPRINTF _snprintf
#else
#include "PosixTimer.h"
#define SNPRINTF snprintf
#endif

static const int32_t NANOSEC_IN_MILLISEC = 1000000;

typedef int64_t test_t;

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;

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

std::string strFromInt64(int64_t num)
{
	const int32_t MIN_INT64_STRLEN = 21; // 19 digits + sign + null terminator
	char chArr[MIN_INT64_STRLEN];
	SNPRINTF(chArr, MIN_INT64_STRLEN, "%lld", static_cast<long long int>(num));
	return std::string(chArr);
}

std::string nsTimeToStr(int64_t ns)
{
	string str = strFromInt64(ns);
	str.append(" us (");
	str.append(strFromInt64(ns / NANOSEC_IN_MILLISEC));
	str.append(" ms)");
	return str;
}

void benchVector(int size)
{
	vector<test_t> testVec;

#ifdef WIN32
	WinTimer timer(1); // us
#else
	PosixTimer timer(1); // us
#endif

	fillVector(testVec, size);
	cout << "Vector fill, " << size << " elements: " << nsTimeToStr(timer.TimeElapsed()) << endl;

	timer.RestartTimer();
	int64_t sum = iterateVector(testVec);
	cout << "Vector itereate, " << size << " elements: " << nsTimeToStr(timer.TimeElapsed()) << " (test sum = " << sum << ")" << endl;

	return;
}

void benchSet(int size)
{
	set<test_t> testSet;

#ifdef WIN32
	WinTimer timer(1); // us
#else
	PosixTimer timer(1); // us
#endif

	fillSet(testSet, size);
	cout << "Set fill, " << size << " elements: " << nsTimeToStr(timer.TimeElapsed()) << endl;

	timer.RestartTimer();
	int64_t sum = iterateSet(testSet);
	cout << "Set itereate, " << size << " elements: " << nsTimeToStr(timer.TimeElapsed()) << " (test sum = " << sum << ")" << endl;

	return;
}

int main()
{
	for (int64_t size = 100, i = 1; size <= 100000000; size *= 10, i++)
	{
		cout << "Test " << i << endl;
		benchVector(size);
		benchSet(size);
		cout << endl;
	}

	return 0;
}
