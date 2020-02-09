// Codility CountDiv
// Difficuly: respectable
//
// https://app.codility.com/programmers/lessons/5-prefix_sums/count_div
//

#include <iostream>

int solution(int A, int B, int K)
{
	if (A > B)
	{
		return -1;
	}

	if (K == 1)
	{
		return (B - A + 1);
	}

	if (A == B)
	{
		return (A % K == 0) ? 1 : 0;
	}

	int i = A;

	for (int i; i <= B; i++)
	{
		if (i % K == 0)
		{
			break;
		}
	}

	int high = B - (B % K);
	int count = ((high - i) / K) + 1;

	return count;
}

int main()
{
	std::cout << "Solution #1: " << solution(1, 20, 5) << ", expected: 4" << std::endl;
	std::cout << "Solution #2: " << solution(3, 19, 5) << ", expected: 3" << std::endl;
	std::cout << "Solution #3: " << solution(1, 6, 1) << ", expected: 6" << std::endl;

	return 0;
}
