#include "SortedSequence.h"
#include <iostream>

using namespace std;
using namespace sortedsequence;

int main()
{
	setlocale(LC_ALL, "Rus");
	
	SortedSequence<int> A;
	
	A.addelem(1, 11);
	A.addelem(3, 33);
	A.addelem(5, 55);
	A.addelem(6, 66);
	A.addelem(2, 22);
	A.addelem(4, 44);
	
	cout << A << endl;

	_getch();
	return 0;
}
