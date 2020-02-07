// Variant on Codility "Rectangle Builder Greater Area"
//

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
int solution(vector<int> &A, int X)
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
	vector<int> vec1 = { 4, 20, 1, 6, 6, 1, 10, 2, 3, 7, 3, 5, 0, 8, 11, 2, 2, 4, 2, 1, 10, 3, 20, 5 };

	solution(vec1, 4);
	solution(vec1, 5);
	solution(vec1, 6);
	solution(vec1, 7);
	solution(vec1, 20);

	return 0;
}
