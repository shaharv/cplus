#include <assert.h>
#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::string;

void spiral(int32_t n);
void look_and_say(int32_t n, const string& seq);
void oneEditAway(const string& word1, const string& word2);
bool oneEditAwayInternal(const string& word1, const string& word2);
void test_oneEditAway();

void spiral(int32_t n)
{
	if (n <= 0)
	{
		return;
	}

	assert((n <= 25) && ("n too large - table won't fit 80 characters width."));

	int32_t* arr = new int32_t[n * n];

	// allocation failed
	if (arr == 0u)
	{
		return;
	}

	memset(arr, 0, (sizeof(int32_t) * static_cast<size_t>(n * n)));

	int32_t hy = 0;
	int32_t ly = n - 1;
	int32_t lx = 0;
	int32_t rx = n - 1;
	int32_t count = 1;

	while (count <= n*n)
	{
		for (int32_t x = lx; x <= rx; x++)
		{
			arr[(hy * n) + x] = count++;
		}

		hy++;

		for (int32_t y = hy; y <= ly; y++)
		{
			arr[(y * n) + rx] = count++;
		}

		rx--;

		for (int32_t x = rx; x >= lx; x--)
		{
			arr[(ly * n) + x] = count++;
		}

		ly--;

		for (int32_t y = ly; y >= hy; y--)
		{
			arr[(y * n) + lx] = count++;
		}

		lx++;
	}

	for (int32_t i = 0; i < n; i++)
	{
		for (int32_t j = 0; j < n; j++)
		{
			printf("%*d", 4, arr[i * n + j]);
		}

		printf("\n");
	}

	delete[] arr;
}

void look_and_say(int32_t n, const string& seq)
{
	string currSeq = seq;

	cout << currSeq << endl;

	for (int32_t j = 1; j < n; j++)
	{
		string newSeq;
		uint32_t i = 0;

		while(i < currSeq.length())
		{
			char ch = currSeq[i];
			int32_t count = 0;

			while (currSeq[i] == ch)
			{
				i++;
				count++;
			}

			newSeq += static_cast<char>(count + '0');
			newSeq += static_cast<char>(ch);
		}

		cout << newSeq << endl;
		currSeq = newSeq;
	}
}

void oneEditAway(const string& word1, const string& word2)
{
	if (oneEditAwayInternal(word1, word2))
	{
		cout << "Yes! One edit away: '" << word1 << "', '" << word2 << "'" << endl;
	}
	else
	{
		cout << "Oops! Not one edit away: '" << word1 << "', '" << word2 << "'" << endl;
	}
}

bool oneEditAwayInternal(const string& word1, const string& word2)
{
	int32_t lenDiff = word1.length() - word2.length();

	if ((lenDiff != 0) && (lenDiff != 1) && (lenDiff != -1))
	{
		return false;
	}

	uint32_t word1Idx = 0;
	uint32_t word2Idx = 0;

	while((word1[word1Idx] != 0u) &&
		(word2[word2Idx] != 0u))
	{
		if (word1[word1Idx] == word2[word2Idx])
		{
			word1Idx++;
			word2Idx++;
			continue;
		}

		if ((word1[word1Idx] != word2[word2Idx + 1]) &&
			(word1[word1Idx + 1] != word2[word2Idx]))
		{
			return false;
		}

		if (word1[word1Idx] == word2[word2Idx + 1])
		{
			word1Idx++;
		}
		else
		{
			word2Idx++;
		}
	}

	if (word1[word1Idx] == word2[word2Idx])
	{
		return true;
	}

	return false;
}

void test_oneEditAway()
{
	oneEditAway("", "a");
	oneEditAway("aba", "aba");
	oneEditAway("abaa", "aba");
	oneEditAway("aba", "abac");
	oneEditAway("caba", "aba");
	oneEditAway("cabac", "aba");
	oneEditAway("111cabac222", "aba");
	oneEditAway("aaaa", "aa");

	cout << endl;
}

int main()
{
	test_oneEditAway();

	const int32_t seqLen = 10;
	const string& lookAndSayBase = "1";
	cout << "Look and say sequence, len = " << seqLen << ", starting \"" << lookAndSayBase << "\":" << endl << endl;
	look_and_say(10, "1");
	cout << endl;

	const int32_t spiralSquareSize = 11;
	cout << "Spiral, size = " << spiralSquareSize << ":" << endl << endl;
	spiral(spiralSquareSize);
	cout << endl;

	return 0;
}
