#pragma once

#include <cstdint>
#include <ctime>

class PosixTimer
{
	int64_t _startTime;
	int32_t _timerRes;

public:
	PosixTimer()
	{
		_timerRes = 1000000; // us

		_startTime = currTimeNs();
	}

	PosixTimer(int64_t timerRes)
	{
		_timerRes = timerRes;

		_startTime = currTimeNs();
	}

	int64_t TimeElapsed()
	{
                int64_t currTime = currTimeNs();

		if (currTime == -1)
		{
                        return -1;
		}

		return (currTime - _startTime) / _timerRes;
	}

	void RestartTimer()
	{
		_startTime = currTimeNs();
	}

private:
	int64_t currTimeNs()
	{
		struct timespec time;

		if (clock_gettime(CLOCK_MONOTONIC, &time) == -1)
		{
			std::cerr << "clock_gettime failed!\n";

                        return -1;
		}

		return (time.tv_nsec + (time.tv_sec * 1000000000));
	}
};
