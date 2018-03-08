#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include "WinTimer.h"
#define SNPRINTF _snprintf
#else
#include "../include/PosixTimer.h"
#define SNPRINTF snprintf
#endif

static const int32_t NANOSEC_IN_MILLISEC = 1000000;

typedef int64_t test_t;

using std::vector;
using std::string;

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

bool setAddr64Bits_V1(int64_t addr)
{
	int32_t bit62 = ((addr & (1ull << 62)) >> 62);
	int32_t bit61 = ((addr & (1ull << 61)) >> 61);
	return (bit62 == bit61);
}

bool setAddr64Bits_V2(int64_t addr)
{
	return (((addr & (3ull << 61)) >> 61) != 2);
}

bool setAddr64Bits_V3(int64_t addr)
{
	return ((addr & 0x6000000000000000ull) != 0x4000000000000000ull);
}

void fillRandom()
{

}

int main()
{
	static const int TESTS = 10;
	static const int MAGNIFY_FACTOR = 100;

	int64_t addrTable[TESTS] = { -1, -10, -100, -1000, -100000, 0x4000000000000000, -6666777788889999, 0x6fff0000ffff0000ll, 0x1234567890abcdell, 0 };
	int64_t totalUs_V1 = 0;
	int64_t totalUs_V2 = 0;
	int64_t totalUs_V3 = 0;

#ifdef WIN32
	WinTimer timer(1); // us
#else
	PosixTimer timer(1); // us
#endif

	for (int j = 0; j < MAGNIFY_FACTOR; j++)
	{
		for (int i = 0; i < TESTS; i++)
		{
			int64_t currTimeUs;

			timer.RestartTimer();
			bool test_V1 = setAddr64Bits_V1(addrTable[i]);
			currTimeUs = timer.TimeElapsed();
			totalUs_V1 += currTimeUs;
			//printf("V1 time = %lldus\n", currTimeUs);

			timer.RestartTimer();
			bool test_V2 = setAddr64Bits_V2(addrTable[i]);
			currTimeUs = timer.TimeElapsed();
			totalUs_V2 += currTimeUs;
			//printf("V2 time = %lldus\n", currTimeUs);

			timer.RestartTimer();
			bool test_V3 = setAddr64Bits_V3(addrTable[i]);
			currTimeUs = timer.TimeElapsed();
			totalUs_V3 += currTimeUs;
			//printf("V3 time = %lldus\n", currTimeUs);

			if ((test_V1 != test_V2) || (test_V1 != test_V3) || (test_V2 != test_V3))
			{
				printf("Test #%d (%llx) failed! Values differ.\n", i, addrTable[i]);
				printf("test_V1 = %d\n", test_V1);
				printf("test_V2 = %d\n", test_V2);
				printf("test_V3 = %d\n", test_V3);
			}
		}
	}

	printf("Total times:\n");
	printf("test_V1 = %lld\n", totalUs_V1);
	printf("test_V2 = %lld\n", totalUs_V2);
	printf("test_V3 = %lld\n", totalUs_V3);

	return 0;
}
