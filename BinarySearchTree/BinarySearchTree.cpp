#include <iostream>
#include "BinarySearchTree.h"
#include "TreeBuilder.h"

using namespace treebuilder;
using namespace binarysearchtree;

int main()
{
	setlocale(LC_ALL, "rus");
	Student X("Василий", "Перепёлкин", "Б16-501", 19);
	Student X1("Афанасий", "Поляков", "Б17-564", 18);
	Student X2("Кирилл", "Поздняков", "Б14-101", 21);
	Student X3("Георгий", "Широков", "Б15-401", 20);
	Student X4("Дмитрий", "Синицын", "Б13-103", 22);
	Student X5("Александр", "Хорохорин", "Б15-403", 20);
	Student X6("Богдан", "Вавилов", "Б16-504", 19);

	SortedSequence<Student> D;

	D.addelem(X.getID(), X);
	D.addelem(X1.getID(), X1);
	D.addelem(X2.getID(), X2);
	D.addelem(X3.getID(), X3);
	D.addelem(X4.getID(), X4);
	D.addelem(X5.getID(), X5);
	D.addelem(X6.getID(), X6);

	TreeBuilder<Student> M;
	BinarySearchTree<Student> A;

	M.Build_BinarySearchTree(A, D);

	/*BinarySearchTree<Student> A;

	A.add_element(X.getID(), X);
	A.add_element(X1.getID(), X1);
	A.add_element(X2.getID(), X2);
	A.add_element(X3.getID(), X3);
	A.add_element(X4.getID(), X4);
	A.add_element(X5.getID(), X5);
	A.add_element(X6.getID(), X6);*/

	A.print_tree();

	/*SortedSequence<int> X;

	
	X.addelem(4, 44);
	X.addelem(6, 66);
	X.addelem(9, 99);
	X.addelem(8, 88);
	X.addelem(10, 1010);
	X.addelem(13, 1313);
	X.addelem(12, 1212);
	X.addelem(14, 1414);

	TreeBuilder<int> C;

	C.Build_BinarySearchTree(A, X);	

	A.print_tree();
	*/
	system("pause");
	return 0;

}
