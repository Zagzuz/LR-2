#include "IDIctionary.h"

using namespace idictionary;

int main()
{
	IDictionary<int> A;

	A.add(1, 1);
	A.add(1, 2);
	
	A.showSimiliar(1);

	system("pause");
    return 0;
}

