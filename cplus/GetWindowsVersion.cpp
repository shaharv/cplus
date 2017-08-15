// Based on the following SO answer:
// https://stackoverflow.com/questions/36543301/detecting-windows-10-version/36545162#36545162

#include <cstdio>
#include <iostream>
#include <string>
#include <windows.h>

typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

#define MAX_WINDOWS_VER_STR_LEN 128

std::string GetWindowsVersion()
{
	std::string winVerStr;
	char verCharArr[MAX_WINDOWS_VER_STR_LEN];

	HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");

	if (hMod == NULL)
	{
		return winVerStr;
	}

	RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");

	if (fxPtr == NULL)
	{
		return winVerStr;
	}

	RTL_OSVERSIONINFOW rovi = { 0 };
	rovi.dwOSVersionInfoSize = sizeof(rovi);

	if (fxPtr(&rovi) != 0x0)
	{
		return winVerStr;
	}

	std::snprintf(verCharArr, MAX_WINDOWS_VER_STR_LEN, "Windows %ld.%ld, build #%ld %ls",
		rovi.dwMajorVersion, rovi.dwMinorVersion, rovi.dwBuildNumber, rovi.szCSDVersion);

	winVerStr = verCharArr;

	return winVerStr;
}

int main()
{
	std::string winVer = GetWindowsVersion();

	std::cout << "OS version: " << winVer << std::endl;

	return 0;
}