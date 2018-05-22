#include <execinfo.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int foo();
int goo();
int zoo();

int foo()
{
	return goo();
}

int goo()
{
	return zoo();
}

int zoo()
{
	// Print function addresses in the stack trace
	const int32_t STACK_DEPTH = 20;
	void* arr[STACK_DEPTH];
	int size = backtrace(arr, STACK_DEPTH);
	backtrace_symbols_fd(arr, size, STDERR_FILENO);

	return 0;
}

int main()
{
	return foo();
}
