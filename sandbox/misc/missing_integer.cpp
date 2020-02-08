// Codility - Missing Integer
// Difficuly: respectable
//
// https://app.codility.com/programmers/lessons/4-counting_elements/missing_integer
//

#include <iostream>
#include <queue>
#include <vector>

int solution(std::vector<int> &A)
{
	int size = A.size();
	std::priority_queue<int, std::deque<int>, std::greater_equal<int> > priorityQ;

	// N logN
	for (int i = 0; i < size; i++)
	{
		if (A[i] > 0)
		{
			priorityQ.push(A[i]);
		}
	}

	int prevTop = 0;
	int top = 0;

	// N
	while (!priorityQ.empty())
	{
		top = priorityQ.top();

		if (top > prevTop + 1)
		{
			return prevTop + 1;
		}

		prevTop = top;

		priorityQ.pop();
	}

	return (top + 1);
}

int main()
{
	std::vector<int> vec1 = { -1, 3, 1 };
	std::vector<int> vec2 = { 0, -1, 2, 2, 3, 1, 4, 6 };

	std::cout << "Solution #1: " << solution(vec1) << ", expected: 2" << std::endl;
	std::cout << "Solution #2: " << solution(vec2) << ", expected: 5" << std::endl;

	return 0;
}
