#pragma once

#include <cstdint>
#include <ctime>

class PosixTimer
{
	int64_t _startTime;
	double _timerRes;

public:
	PosixTimer()
	{
		_timerRes = 1000.0;

		_startTime = currTimeNs();
	}

	PosixTimer(double timerRes)
	{
		_timerRes = timerRes;

		_startTime = currTimeNs();
	}

	double TimeElapsed()
	{
                int64_t currTime = currTimeNs();

		if (currTime == -1)
		{
                        return 0.0;
		}

		return double(currTime - _startTime) / _timerRes;
	}

	void RestartTimer()
	{
		_startTime = currTimeNs();
	}

private:
	int64_t currTimeNs()
	{
		struct timespec time;

		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time) == -1)
		{
			std::cerr << "clock_gettime failed!\n";

                        return -1;
		}

		return time.tv_nsec;
	}
};
