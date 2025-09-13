#include <assert.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

// http://man7.org/linux/man-pages/man7/pthreads.7.html
//
// Used APIs:
// - pthread_create
// - pthread_self
//

typedef struct thread_info
{
	pthread_t tid;
	int32_t tnum;
} thread_info;

static void* run(void* arg)
{
	thread_info *tinfo = reinterpret_cast<thread_info*>(arg);
	pthread_t selfId = pthread_self();
	assert(selfId == tinfo->tid);
	std::cout << "Thread #" << tinfo->tnum << " started. tid = " << tinfo->tid << std::endl;
	return NULL;
}

int main()
{
	static const int32_t THREADS = 5;
	for (int32_t i = 0; i < THREADS; i++)
	{
		thread_info tinfo;
		tinfo.tnum = i;
		int32_t status = pthread_create(&tinfo.tid, NULL, &run, reinterpret_cast<void*>(&tinfo));
		if (status != 0)
		{
			std::cout << "pthread_create failed with error: " << status << std::endl;
		}
		sleep(1);
	}
	return 0;
}
