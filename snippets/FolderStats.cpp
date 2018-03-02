#include <cstdint>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#endif

using std::string;
using std::cout;
using std::endl;

bool folderStats(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files);

#ifdef _WIN32
bool folderStatsWin(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files);
#else
bool posixIsFolder(const char* path);
int posixFileSize(const char* path);
bool folderStatsPosix(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files);
#endif

bool folderStats(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files)
{
	size = subfolders = files = 0;

	#ifdef _WIN32
	return folderStatsWin(path, size, subfolders, files);
	#else
	// Add root folder size (4096) to total size.
	// Result is compatible with "du -sh -B1 --apparent-size".
	size = posixFileSize(path.c_str());
	return folderStatsPosix(path, size, subfolders, files);
	#endif
}

#ifdef _WIN32

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

#else

bool posixIsFolder(const char* path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
	{
		return false;
	}

	return S_ISDIR(statbuf.st_mode);
}

int posixFileSize(const char* path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
	{
		return 0;
	}

	return statbuf.st_size;
}

bool folderStatsPosix(string path, uint64_t& size, uint64_t& subfolders, uint64_t& files)
{
	DIR *dirp;
	struct dirent *dirEntry;

	if ((dirp = opendir(path.c_str())) == NULL)
	{
		return false;
	}

	while ((dirEntry = readdir(dirp)) != NULL)
	{
		string curEntry = path + "/" + string(dirEntry->d_name);

		if (posixIsFolder(curEntry.c_str()))
		{
			if ((strncmp(dirEntry->d_name, ".", 2) == 0) ||
				(strncmp(dirEntry->d_name, "..", 3) == 0))
			{
				continue;
			}

			subfolders++;

			if (!folderStatsPosix(curEntry, size, subfolders, files))
			{
				return false;
			}
		}
		else
		{
			files++;
		}

		size += posixFileSize(curEntry.c_str());
	}

	closedir(dirp);

	return true;
}

#endif

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
