// Variant on Codility "Rectangle Builder Greater Area"
//

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::vector;

// X, A[i] = [1...1B]
// A size < 100,000
//
int solution_attempt(vector<int> &A, int X)
{
	map<int, int> fencePieces;

	cout << "Looking for pens of size bigger/equal to " << X << "..." << endl;

	// O(klog(k))
	//
	for (vector<int>::const_iterator it = A.begin(); it != A.end(); ++it)
	{
		fencePieces[*it]++;
	}

	int possiblePens = 0;
	vector<int> sortedRectPenPieces;

	// O(k)
	//
	for (map<int, int>::const_iterator it = fencePieces.begin(); it != fencePieces.end(); ++it)
	{
		int piece = it->first;
		int count = it->second;

		if (count < 2)
		{
			continue;
		}

		if (piece * piece >= X && count >= 4)
		{
			cout << "Pen found: " << piece << " * " << piece << endl;
			possiblePens++;
		}

		sortedRectPenPieces.push_back(piece);
	}

	// O(k^2 * logk)
	//
	for (vector<int>::iterator it = sortedRectPenPieces.begin(); it != sortedRectPenPieces.end(); ++it)
	{
		int piece = *it;
		vector<int>::iterator firstMatchingPieceIt;

		if (piece >= X)
		{
			firstMatchingPieceIt = it;
		}
		else
		{
			int smallestMatchingPiece = X / piece;
			if (X % piece > 0)
			{
				smallestMatchingPiece++;
			}

			// find smallest piece >= smallestMatchingPiece: O(logk)
			//
			firstMatchingPieceIt = std::lower_bound(it, sortedRectPenPieces.end(), smallestMatchingPiece);

			if (firstMatchingPieceIt == sortedRectPenPieces.end())
			{
				continue;
			}
		}

		// O(k)
		for (vector<int>::iterator it2 = firstMatchingPieceIt; it2 != sortedRectPenPieces.end(); ++it2)
		{
			int foundPiece = *it2;
			assert(foundPiece * piece >= X);

			// square pens already handled
			//
			if (piece != foundPiece)
			{
				possiblePens++;
				cout << "Pen found: " << piece << " * " << foundPiece << endl;
			}
		}
	}

	return possiblePens;
}

// X, A[i] = [1...1B]
// A size < 100,000
//
int solution_exact_area(vector<int> &A, int X)
{
	map<int, int> fencePieces;
	int possiblePens = 0;

	cout << "Looking for pens of size " << X << "..." << endl;

	// O(klog(k))
	//
	for (vector<int>::const_iterator it = A.begin(); it != A.end(); ++it)
	{
		fencePieces[*it]++;
	}

	// O(klog(k))
	//
	for (map<int, int>::const_iterator it = fencePieces.begin(); it != fencePieces.end(); ++it)
	{
		int piece = it->first;
		int count = it->second;

		// Stop looking after X / 2, to avoid redudant lookup
		//
		if (piece > X / 2)
		{
			break;
		}

		if ((count < 2) || (X % piece != 0))
		{
			continue;
		}

		int matchingPiece = X / piece;

		if ((piece == matchingPiece) && (fencePieces[piece] >= 4))
		{
			possiblePens++;
			cout << "Pen found: " << piece << " * " << X / piece << endl;
		}
		if ((fencePieces[X / piece] >= 2) && (piece < matchingPiece))
		{
			possiblePens++;
			cout << "Pen found: " << piece << " * " << X / piece << endl;
		}
	}

	cout << "Total pens of size " << X << ": " << possiblePens << endl << endl;

	return possiblePens;
}

int main()
{
	vector<int> vec1 = { 4, 20, 1, 6, 6, 1, 10, 2, 3, 7, 3, 5, 0, 8, 11, 2, 2, 4, 2, 1, 10, 3, 20, 5, 20, 20, 11 };

	solution_exact_area(vec1, 4);
	solution_exact_area(vec1, 5);
	solution_exact_area(vec1, 6);
	solution_exact_area(vec1, 7);
	solution_exact_area(vec1, 20);

	solution_attempt(vec1, 4);
	solution_attempt(vec1, 5);
	solution_attempt(vec1, 6);
	solution_attempt(vec1, 7);
	solution_attempt(vec1, 20);
	solution_attempt(vec1, 1000);
	solution_attempt(vec1, 1);
	solution_attempt(vec1, 40);
	solution_attempt(vec1, 100);

	return 0;
}
