#include <iostream>
#include <windows.h>

void PrintEnvVariables()
{
	static const int maxEnvVarLenPrinted = 2048;
	char curEnvVar[maxEnvVarLenPrinted + 1];

	LPCH envStr = GetEnvironmentStrings();

	if (envStr == NULL)
	{
		return;
	}

	// GetEnvironmentStrings returns a pointer to the environment block of the current process.
	// Variable strings are separated by NULL byte, and the block is terminated by a NULL byte.
	for (LPTSTR envVarChar = (LPTSTR)envStr; *envVarChar; envVarChar++)
	{
		int charIdx = 0;

		while (*envVarChar)
		{
			char currChar = *envVarChar++;
			if (charIdx < maxEnvVarLenPrinted)
			{
				curEnvVar[charIdx++] = currChar;
			}
		}

		curEnvVar[charIdx] = 0;

		printf("%s\n", curEnvVar);
	}

	BOOL freeEnvStr = FreeEnvironmentStrings(envStr);

	if (freeEnvStr == 0)
	{
		std::cout << "Error returned from FreeEnvironmentStrings" << std::endl;
	}
}

int main()
{
	PrintEnvVariables();

	return 0;
}
