// Based on code example from:
// https://msdn.microsoft.com/en-us/library/hskdteyh.aspx

// InstructionSet.cpp   
// Compile by using: cl /EHsc /W4 InstructionSet.cpp  
// processor: x86, x64  
// Uses the __cpuid intrinsic to get information about   
// CPU extended instruction set support. 

#include <iostream>  
#include <vector>  
#include <array>  
#include <string>  
#include <intrin.h>  

std::string GetCPUBrand()
{
	int nExIds;
	std::string brandStr;
	std::array<int, 4> cpui;
	std::vector<std::array<int, 4>> extdata;

	// Calling __cpuid with 0x80000000 as the function_id argument  
	// gets the number of the highest valid extended ID.  
	__cpuid(cpui.data(), 0x80000000);
	nExIds = cpui[0];

	char brandArr[0x40];
	memset(brandArr, 0, sizeof(brandArr));

	for (int i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuidex(cpui.data(), i, 0);
		extdata.push_back(cpui);
	}

	// Interpret CPU brand string if reported  
	if (nExIds >= 0x80000004)
	{
		memcpy(brandArr, extdata[2].data(), sizeof(cpui));
		memcpy(brandArr + 16, extdata[3].data(), sizeof(cpui));
		memcpy(brandArr + 32, extdata[4].data(), sizeof(cpui));
		brandStr = brandArr;
	}

	return brandStr;
}

// Print out supported instruction set extensions  
int main()
{
	std::string cpuBrand = GetCPUBrand();

	std::cout << "CPU brand: " << cpuBrand << std::endl;

	return 0;
}
