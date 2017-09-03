#include <iostream>
#include "windows.h"

#include "WinTimer.h"

const double WinTimer::_timerRes = 1000.0; // ms

WinTimer::WinTimer()
{
	initTimer();

	_timeStart = CurrTime();
}

void WinTimer::initTimer()
{
	LARGE_INTEGER li;

	if (!QueryPerformanceFrequency(&li))
	{
		std::cerr << "QueryPerformanceFrequency failed!\n";
	}

	_timeFreq = double(li.QuadPart) / 1000.0;
}

int64_t WinTimer::CurrTime()
{
	LARGE_INTEGER li;

	QueryPerformanceCounter(&li);

	return li.QuadPart;
}

double WinTimer::TimeElapsed()
{
	LARGE_INTEGER li;
	
	QueryPerformanceCounter(&li);
	
	return double(li.QuadPart - _timeStart) / _timeFreq;
}

void WinTimer::RestartTimer()
{
	_timeStart = CurrTime();
}
