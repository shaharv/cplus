#pragma once

#include <cstdint>
#include <iostream>
#include <windows.h>

class WinTimer
{
	int64_t _timeStart;
	double _timeFreq;
	double _timerRes;

public:
	WinTimer()
	{
		WinTimer(1000.0);
	}

	WinTimer(double timerRes)
	{
		_timerRes = timerRes;
		initTimer();
		_timeStart = CurrTime();
	}

	double TimeElapsed()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return double(li.QuadPart - _timeStart) / _timeFreq;
	}

	void RestartTimer()
	{
		_timeStart = CurrTime();
	}

private:
	void initTimer()
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
		{
			std::cerr << "QueryPerformanceFrequency failed!\n";
		}
		_timeFreq = double(li.QuadPart) / _timerRes;
	}

	int64_t CurrTime()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return li.QuadPart;
	}
};
