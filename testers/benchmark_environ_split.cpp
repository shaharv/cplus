#include <cstring>
#include <iostream>
#include <vector>

#include <unistd.h>
#include "PosixTimer.h"

typedef int64_t test_t;

#define SNPRINTF snprintf

using std::cout;
using std::endl;
using std::vector;
using std::string;

std::string strFromInt64(int64_t num)
{
	const int32_t MIN_INT64_STRLEN = 21; // 19 digits + sign + null terminator
	char chArr[MIN_INT64_STRLEN];
	SNPRINTF(chArr, MIN_INT64_STRLEN, "%lld", static_cast<long long int>(num));
	return std::string(chArr);
}

std::string nsTimeToStr(int64_t ns)
{
	const int32_t NANOSEC_IN_MILLISEC = 1000000;
	string str = strFromInt64(ns);
	str.append(" us (");
	str.append(strFromInt64(ns / NANOSEC_IN_MILLISEC));
	str.append(" ms)");
	return str;
}

void getEnvVars_v1(vector<string>* envVars)
{
	PosixTimer timer(1);

	for (char* envVarChar = *environ; *envVarChar != '\0'; envVarChar++)
	{
		char* name = envVarChar;

		// Scan the string till '=' or null
		for (; (*envVarChar != '\0') && (*envVarChar != '='); envVarChar++);

		char* value = envVarChar;

		// Scan the string till null
		for (; *envVarChar != '\0'; envVarChar++);

		// System Environment Variable (name is missing)
		if (value == name)
		{
			continue;
		}

		string varname(name, value - name);
		string varval(++value);

		#ifdef DEBUG_VARS
		cout << varname << "=" << varval << endl;
		#endif

		envVars->push_back(varname);
		envVars->push_back(varval);
	}

	cout << "getEnvVars_v1: " << nsTimeToStr(timer.TimeElapsed()) << endl;
}

void getEnvVars_v2(vector<string>* envVars)
{
	PosixTimer timer(1);

	for (char* envVarStr = *environ; *envVarStr != '\0'; envVarStr = strchr(envVarStr, '\0') + 1)
	{
		const char* envVarSeperator = strchr(envVarStr, '=');

		if (envVarSeperator == 0 || envVarSeperator == envVarStr)
		{
			continue;
		}

		string varname = string(envVarStr, envVarSeperator - envVarStr);
		string varval = string((char*)(envVarSeperator + 1));

		#ifdef DEBUG_VARS
		cout << varname << "=" << varval << endl;
		#endif

		envVars->push_back(varname);
		envVars->push_back(varval);
	}

	cout << "getEnvVars_v2: " << nsTimeToStr(timer.TimeElapsed()) << endl;
}

int main()
{
	const int32_t TEST_ITERATIONS = 10;

	for (int i = 0; i < TEST_ITERATIONS; i++)
	{
		vector<string> envVarsV1;
		vector<string> envVarsV2;

		getEnvVars_v1(&envVarsV1);
		getEnvVars_v2(&envVarsV2);
	}

	return 0;
}
