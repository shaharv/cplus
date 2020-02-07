// Codility - Smallest Integer
//

#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::set;
using std::vector;

int solution(vector<int> &A)
{
	set<int> sortedPositives;

	// sort and discard non-positives, remove duplicates: O(k * log(k))
	//
	for (vector<int>::const_iterator it = A.begin(); it != A.end(); ++it)
	{
		if (*it > 0)
		{
			sortedPositives.insert(*it);
		}
	}

	if (sortedPositives.empty())
	{
		return 1;
	}

	int smallestInt = 1;

	// Iterate the set: O(k * log(k))
	//
	for (set<int>::const_iterator it = sortedPositives.begin(); it != sortedPositives.end(); ++it)
	{
		if (smallestInt < *it)
		{
			return smallestInt;
		}
		else if (smallestInt == *it)
		{
			smallestInt++;
		}
		else
		{
			smallestInt = *it;
		}
	}

	return smallestInt;
}

int main()
{
	vector<int> vec1 = { -8, 1, 2, 4, 3, 1, 6 };
	vector<int> vec2 = { 1, 3 };
	vector<int> vec3 = { 0, 99, -1, 8, 4, 3 };

	int sol1 = solution(vec1);
	int sol2 = solution(vec2);
	int sol3 = solution(vec3);

	cout << "Solution #1 = " << sol1 << ", expected = 5" << endl;
	cout << "Solution #2 = " << sol2 << ", expected = 2" << endl;
	cout << "Solution #3 = " << sol3 << ", expected = 1" << endl;

	return 0;
}
