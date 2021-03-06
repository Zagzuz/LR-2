#include "gtest/gtest.h"
#include "SortedSequence.h"
#include "BinarySearchTree.h"
#include "Idictionary.h"
#include "BTree.h"
#include "Student.h"

using namespace binarysearchtree;
using namespace sortedsequence;
using namespace btree;
using namespace idictionary;

TEST(SortedSequence, Constructor)
{
	SortedSequence<int> A;
	ASSERT_EQ(A.getLength(), 0);
	A.addelem(1, 11);
	A.addelem(2, 22);
	A.addelem(3, 33);
	A.addelem(4, 44);

	SortedSequence<int> B(A);
	ASSERT_EQ(B.getLength(), 4);
	ASSERT_EQ(B.getValue(B.BinSearch(1)), 11);
	ASSERT_EQ(B.getValue(B.BinSearch(2)), 22);
	ASSERT_EQ(B.getValue(B.BinSearch(3)), 33);
	ASSERT_EQ(B.getValue(B.BinSearch(4)), 44);
}

TEST(SortedSequence, add_find_remove)
{
	SortedSequence<int> B;
	ASSERT_EQ(B.getLength(), 0);
	
	B.addelem(1, 11); 
	ASSERT_EQ(B.getLength(), 1);
	
	B.addelem(2, 22);
	ASSERT_EQ(B.getLength(), 2);
	
	B.addelem(3, 33); 
	ASSERT_EQ(B.getLength(), 3);

	B.addelem(4, 44); 
	ASSERT_EQ(B.getLength(), 4);

	ASSERT_EQ(B.getValue(B.BinSearch(1)), 11);
	
	ASSERT_EQ(B.getValue(B.BinSearch(2)), 22);
	
	ASSERT_EQ(B.getValue(B.BinSearch(3)), 33);
	
	ASSERT_EQ(B.getValue(B.BinSearch(4)), 44);
	
	B.delelem(4);
	ASSERT_EQ(B.BinSearch(4), -1);
	ASSERT_EQ(B.getLength(), 3);

	B.delelem(3);
	ASSERT_EQ(B.BinSearch(3), -1);
	ASSERT_EQ(B.getLength(), 2);

	B.delelem(2);
	ASSERT_EQ(B.BinSearch(2), -1);
	ASSERT_EQ(B.getLength(), 1);

	B.delelem(1);
	ASSERT_EQ(B.BinSearch(1), -1);
	ASSERT_EQ(B.getLength(), 0);
}

TEST(SortedSequence, methods)
{
	SortedSequence<int> A;
	ASSERT_EQ(A.getLength(), 0);
	
	A.addelem(0, 0);
	A.addelem(1, 11);
	A.addelem(2, 22);
	A.addelem(3, 33);
	A.addelem(4, 44);
	A.addelem(5, 55);
	
	ASSERT_EQ(A[0], 0);
	ASSERT_EQ(A[1], 11);
	ASSERT_EQ(A[2], 22);
	ASSERT_EQ(A[3], 33);
	ASSERT_EQ(A[4], 44);
	ASSERT_EQ(A[5], 55);

	ASSERT_EQ(A.getLength(), 6);

	A.rewrite(0, 1);
	ASSERT_EQ(A[0], 1);

	A.delelem(0);
	A.delelem(1);
	A.delelem(2);

	ASSERT_EQ(A[0], NULL);
	ASSERT_EQ(A[1], NULL);
	ASSERT_EQ(A[2], NULL);
}

TEST(BinarySearchTree, methods)
{
	BinarySearchTree<double> D;
	ASSERT_TRUE(D.IsEmpty());

	D.add_element(2, 2.84);
	D.add_element(1, 2.34);
	D.add_element(4, 23.234);
	D.add_element(5, 234.34542);

	ASSERT_FALSE(D.IsEmpty());
	
	ASSERT_EQ(D.getValue(2), 2.84);
	ASSERT_EQ(D.getValue(1), 2.34);
	ASSERT_EQ(D.getValue(4), 23.234);
	ASSERT_EQ(D.getValue(5), 234.34542);

	D.delete_element(2);
	D.delete_element(1);
	D.delete_element(4);
	D.delete_element(5);

	ASSERT_EQ(D.search_element(2), nullptr);
	ASSERT_EQ(D.search_element(1), nullptr);
	ASSERT_EQ(D.search_element(4), nullptr);
	ASSERT_EQ(D.search_element(5), nullptr);

	ASSERT_TRUE(D.IsEmpty());
}

TEST(BTree, methods)
{
	BTree<int> B(6);
	ASSERT_TRUE(B.IsEmpty());

	B.insert(7, 777);
	B.insert(3, 333);
	B.insert(1, 111);
	B.insert(5, 555);
	B.insert(11, 111111);

	ASSERT_EQ(B.getValue(5), 555);
	ASSERT_EQ(B.getValue(3), 333);
	ASSERT_EQ(B.getValue(1), 111);
	ASSERT_EQ(B.getValue(7), 777);
	ASSERT_EQ(B.getValue(11), 111111);
	
	B.remove(3);
	B.remove(5);
	B.remove(1);
	B.remove(7);
	B.remove(11);

	ASSERT_TRUE(B.IsEmpty());
}

TEST(IDictionary, methods)
{
	IDictionary<string> S;
	ASSERT_EQ(S.GetCount(), 0);

	S.add(1, "2833");
	S.add(9, "2833");

	ASSERT_EQ(S.GetCapacity(), 2);

	ASSERT_EQ(S.returnelem(1), "2833");
	ASSERT_EQ(S.returnelem(9), "2833");
}

TEST(Student, methods)
{
	Student A;
	ASSERT_EQ(A.getAge(), 0);
	
	Student B("Ivan", "Ivanov", "a11-111", 20);
	ASSERT_EQ(B.getAge(), 20);
	ASSERT_EQ(B.getName(), "Ivan");
	ASSERT_EQ(B.getSurname(), "Ivanov");
	ASSERT_EQ(B.getGroup(), "a11-111");
	
	B.changeGroup("a11-112");
	ASSERT_EQ(B.getGroup(), "a11-112");
	B.IncAge();
	ASSERT_EQ(B.getAge(), 21);
}

void main(int argc, char **argv)
{
	setlocale(LC_ALL, "Rus");
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}
