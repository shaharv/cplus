#pragma once

#include <cstdint>
#include <windows.h>

class WinTimer
{
	int64_t _timeStart;
	double _timeFreq;
	static const double _timerRes;

public:
	WinTimer();
	__declspec(noinline) double TimeElapsed();
	__declspec(noinline) void RestartTimer();

private:
	void initTimer();
	__declspec(noinline) int64_t CurrTime();
};
