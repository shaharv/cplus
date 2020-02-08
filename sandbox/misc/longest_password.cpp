// Codility LongestPassword
//

#include <algorithm>
#include <iostream>
#include <locale>
#include <string>

using std::cout;
using std::endl;
using std::max;
using std::string;

bool validPass(const string& str);

int solution(const string &S)
{
	int longestPass = -1;
	int wordIndex = 0;

	for (int i = 0; i < (int)S.length(); i++)
	{
		if (S[i] == ' ')
		{
			string word(S, wordIndex, i - wordIndex);

			if (validPass(word))
			{
				longestPass = max((int)word.length(), longestPass);
			}

			wordIndex = i + 1;
		}
	}

	string lastWord(S, wordIndex, S.length());

	if (validPass(lastWord))
	{
		longestPass = max((int)lastWord.length(), longestPass);
	}

	return longestPass;
}

bool validPass(const string& str)
{
	int letters = 0;
	int digits = 0;

	for (int i = 0; i < (int)str.length(); i++)
	{
		if (!isalnum(str[i]))
		{
			return false;
		}

		if ((str[i] >= '0') && (str[i] <= '9'))
		{
			digits++;
		}
		else
		{
			letters++;
		}
	}

	return ((letters % 2 == 0) && (digits % 2 == 1));
}

int main()
{
	cout << "Solution #1: " << solution("1ab") << endl;
	cout << "Solution #2: " << solution("1 2 3 a") << endl;
	cout << "Solution #3: " << solution("1 2 3 a ?? ab1 pass5") << endl;

	return 0;
}
