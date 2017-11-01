#include <cstdint>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/statvfs.h>
#endif

using std::cerr;
using std::cout;
using std::endl;

#ifdef _WIN32

bool GetDiskSpace(uint64_t& availBytes, uint64_t& totalBytes, uint64_t& totalFreeBytes)
{
	ULARGE_INTEGER availBytesPar;
	ULARGE_INTEGER totalBytesPar;
	ULARGE_INTEGER totalFreeBytesPar;

	if (!GetDiskFreeSpaceEx(NULL, &availBytesPar, &totalBytesPar, &totalFreeBytesPar))
	{
		return false;
	}

	availBytes = static_cast<uint64_t>(availBytesPar.QuadPart);
	totalBytes = static_cast<uint64_t>(totalBytesPar.QuadPart);
	totalFreeBytes = static_cast<uint64_t>(totalFreeBytesPar.QuadPart);

	return true;
}

#else

bool GetDiskSpace(uint64_t& availBytes, uint64_t& totalBytes, uint64_t& totalFreeBytes)
{
	struct statvfs buffer;

	if (statvfs("/usr", &buffer))
	{
		return false;
	}

	availBytes = static_cast<uint64_t>(buffer.f_bavail * buffer.f_frsize);
	totalBytes = static_cast<uint64_t>(buffer.f_blocks * buffer.f_frsize);
	totalFreeBytes = static_cast<uint64_t>(buffer.f_bfree * buffer.f_frsize);

	return true;
}

#endif

int main()
{
	uint64_t availBytes, totalBytes, totalFreeBytes;

	bool result = GetDiskSpace(availBytes, totalBytes, totalFreeBytes);

	if (!result)
	{
		cerr << "Error: GetDiskSpace failed." << endl;
		return 0;
	}

	cout << "Available space (bytes): " << availBytes << endl;
	cout << "Total space (bytes):     " << totalBytes << endl;
	cout << "Free disk space (bytes): " << totalFreeBytes << endl;

	return 0;
}
