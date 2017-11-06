#include <cstdint>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using std::string;
using std::cout;
using std::endl;

bool folderStats(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files);

#ifdef _WIN32
bool folderStatsWin(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files);
#endif

bool folderStats(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files)
{
	size = subfolders = files = 0;

	#ifdef _WIN32
	return folderStatsWin(path, size, subfolders, files);
	#else
	return false;
	#endif
}

bool folderStatsWin(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files)
{
	WIN32_FIND_DATA data;
	string wildcard = path + "\\*.*";
	HANDLE h = FindFirstFile(wildcard.c_str(), &data);

	if (h == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	do
	{
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if ((strncmp(data.cFileName, ".", 2) == 0) ||
				(strncmp(data.cFileName, "..", 3) == 0))
			{
				continue;
			}

			if (data.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
			{
				continue;
			}
			
			subfolders++;

			if (!folderStatsWin(path + "\\" + data.cFileName, size, subfolders, files))
			{
				return false;
			}
		}
		else
		{
			files++;

			LARGE_INTEGER sz;
			sz.LowPart = data.nFileSizeLow;
			sz.HighPart = data.nFileSizeHigh;
			size += sz.QuadPart;
		}
	}
	while (FindNextFile(h, &data) != 0);

	FindClose(h);

	return true;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		cout << "Please specify a folder path." << endl;
		return 0;
	}
	
	uint64_t size, subfolders, files;

	if (!folderStats(argv[1], size, subfolders, files))
	{
		cout << "Not a valid folder path." << endl;
		return 0;
	}

	cout << "Folder       : " << argv[1]    << endl;
	cout << "  size       : " << size       << endl;
	cout << "  subfolders : " << subfolders << endl;
	cout << "  files      : " << files      << endl;

	return 0;
}
