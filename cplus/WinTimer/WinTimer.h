#pragma once

#include <cstdint>

class WinTimer
{
	int64_t _timeStart;
	double _timeFreq;
	double _timerRes;

public:
	WinTimer();
	WinTimer(double timeRes);
	__declspec(noinline) double TimeElapsed();
	__declspec(noinline) void RestartTimer();

private:
	void initTimer();
	__declspec(noinline) int64_t CurrTime();
};
