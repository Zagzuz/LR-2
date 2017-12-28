#pragma once 

#include "BinarySearchTree.h"
#include "SortedSequence.h"
#include "c:/Users/Руслан/source/repos/LR-2/BTree/BTree.h"

using namespace sortedsequence;
using namespace binarysearchtree;
using namespace btree;

namespace treebuilder
{
	template <typename T>
	class TreeBuilder
	{
	public:
		TreeBuilder(){}
		~TreeBuilder(){}
		void Build_BinarySearchTree(BinarySearchTree<T> &, SortedSequence<T> &);
		void Build_BTree(BTree<T> &, SortedSequence<T> &);
	};

	template<typename T>
	void TreeBuilder<T>::Build_BTree(BTree<T> &BT, SortedSequence<T> &SQN)
	{
		for (int i = 0; i < SQN.getLength(); i++)
			BT.insert(SQN.getKey(i), SQN.getValue(i));
	}

	template <typename T>
	void TreeBuilder<T>::Build_BinarySearchTree(BinarySearchTree<T> &BST, SortedSequence<T> &SQN)
	{
		for (int i = 0; i < SQN.getLength(); i++)
			BST.add_element(SQN.getKey(i), SQN.getValue(i));
	}
}
