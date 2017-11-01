#include <cstdint>
#include <iostream>
#include <windows.h>

using std::cerr;
using std::cout;
using std::endl;

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

int main()
{
	uint64_t availBytes, totalBytes, totalFreeBytes;
	
	bool result = GetDiskSpace(availBytes, totalBytes, totalFreeBytes);
	
	if (!result)
	{
		cerr << "Error: GetDiskFreeSpaceEx failed." << endl;
		return 0;
	}

	cout << "Available space (bytes): " << availBytes << endl;
	cout << "Total space (bytes):     " << totalBytes << endl;
	cout << "Free disk space (bytes): " << totalFreeBytes << endl;

	return 0; 
}
