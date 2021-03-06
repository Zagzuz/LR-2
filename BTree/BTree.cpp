#pragma once

#include <iostream>
#include "BTree.h"
#include "SortedSequence.h"
#include "TreeBuilder.h"
#include "Student.h"

using namespace btree;
using namespace treebuilder;
using namespace sortedsequence;
using namespace student;

int main()
{
	setlocale(LC_ALL, "rus");
	int t;
	std::cout << "Enter t:" << endl;
	getNum(t, 0, -1);
	
	BTree<Student> A(t);

	SortedSequence<Student> D;
	
	Student X("Василий", "Перепёлкин", "Б16-501", 19);
	Student X1("Афанасий", "Поляков", "Б17-564", 18);
	Student X2("Кирилл", "Поздняков", "Б14-101", 21);
	Student X3("Георгий", "Широков", "Б15-401", 20);
	Student X4("Дмитрий", "Синицын", "Б13-103", 22);
	Student X5("Александр", "Хорохорин", "Б15-403", 20);
	Student X6("Богдан", "Вавилов", "Б16-504", 19);

	D.addelem(X.getID(), X);
	D.addelem(X1.getID(), X1);
	D.addelem(X2.getID(), X2);
	D.addelem(X3.getID(), X3);
	D.addelem(X4.getID(), X4);
	D.addelem(X5.getID(), X5);
	D.addelem(X6.getID(), X6);

	TreeBuilder<Student> M;

	M.Build_BTree(A, D);

	A.traverse();

	/*SortedSequence<int> X;

	X.addelem(7, 77);
	X.addelem(3, 33);
	X.addelem(11, 1111);
	X.addelem(5, 55);
	X.addelem(1, 11);
	X.addelem(2, 22);
	X.addelem(4, 44);
	X.addelem(6, 66);
	X.addelem(9, 99);
	X.addelem(8, 88);
	X.addelem(10, 1010);
	X.addelem(13, 1313);
	X.addelem(12, 1212);
	X.addelem(14, 1414);

	TreeBuilder<int> C;

	C.Build_BTree(A, X);

	A.traverse();*/

	/*
	std::cout << "0.exit" << std::endl;
	std::cout << "1.add" << std::endl;
	std::cout << "2.search" << std::endl;
	std::cout << "3.remove" << std::endl;
	std::cout << "4.print" << std::endl;
	
	int ch = 1;
	while (ch)
	{
		getNum(ch, -1, 4);
		switch (ch)
		{
		case 1:
			X.Add();
			break;
		case 2:
			X.Find();
			break;
		case 3:
			X.Delete();
			break;
		case 4:
			X.traverse();
			break;
		}
	}
	*/

	system("pause");

	return 0;
}

