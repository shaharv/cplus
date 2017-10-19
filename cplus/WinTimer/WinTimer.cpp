#include <iostream>
#include <windows.h>

#include "WinTimer.h"

WinTimer::WinTimer()
{
	WinTimer(1000.0);
}

WinTimer::WinTimer(double timerRes)
{
	_timerRes = timerRes;

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

	_timeFreq = double(li.QuadPart) / _timerRes;
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
