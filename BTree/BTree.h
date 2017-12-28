#pragma once

#include <iostream>
#include <algorithm>
#include "BinarySearchTree.h"

using namespace binarysearchtree;
using namespace std;

namespace btree
{
	class BTreeNode
	{
		int * keys;
		int t;      
		BTreeNode ** C; 
		int n;     
		bool leaf;
	public:
		BTreeNode(int _t, bool _leaf); 
		void insertNonFull(int k);
		void splitChild(int i, BTreeNode *y);
		template <typename T> void traverse(SortedSequence<T> &a);
		BTreeNode * search(int k);   
		void borrowFromNext(int);
		void borrowFromPrev(int);
		void merge(int);
		int findKey(int);
		int getPred(int);
		int getSucc(int);
		void removeFromNonLeaf(int);
		void removeFromLeaf(int);
		void remove(int);
		void fill(int);
		template <typename T> friend class BTree;
	};

	
	BTreeNode::BTreeNode(int t1, bool leaf1)
	{
		t = t1;
		leaf = leaf1;
		keys = new int[2 * t - 1];
		C = new BTreeNode * [2 * t];
		n = 0;
	}

	template <typename T>
	void BTreeNode::traverse(SortedSequence<T> &a)
	{
		int i;

		for (i = 0; i < n; i++)
		{
			if (leaf == false) C[i]->traverse(a);
			cout << "key: " << keys[i] << '\t';
			cout << "value: " << a.keygetValue(keys[i]) << endl;
		}		
	}

	BTreeNode * BTreeNode::search(int key)
	{
		int i = 0;
		while (i < n && key > keys[i]) i++;

		if (keys[i] == key)
			return this;

		if (leaf == true)
			return nullptr;

		return C[i]->search(key);
	}

	void BTreeNode::insertNonFull(int key)
	{
		int i = n - 1;

		if (leaf == true)
		{
			while (i >= 0 && keys[i] > key)
			{
				keys[i + 1] = keys[i];
				i--;
			}

			keys[i + 1] = key;
			n = n + 1;
		}
		else 
		{
			while (i >= 0 && keys[i] > key) i--;

			if (C[i + 1]->n == 2 * t - 1)
			{
				splitChild(i + 1, C[i + 1]);
				if (keys[i] < key) i++;
			}

			C[i + 1]->insertNonFull(key);
		}
	}

	void BTreeNode::splitChild(int i, BTreeNode * y)
	{
		BTreeNode * z = new BTreeNode(y->t, y->leaf);

		z->n = t - 1;

		for (int j = 0; j < t - 1; j++)
		{
			z->keys[j] = y->keys[j + t];
		}

		if (y->leaf == false)
		{
			for (int j = 0; j < t; j++)
				z->C[j] = y->C[j + t];
		}

		y->n = t - 1;

		for (int j = n; j >= i + 1; j--)
			C[j + 1] = C[j];
		C[i + 1] = z;

		for (int j = n - 1; j >= i; j--)
		{
			keys[j + 1] = keys[j];
		}

		keys[i] = y->keys[t - 1];

		n++;
	}

	int BTreeNode::findKey(int key)
	{
		int idx = 0;
		while (idx < n && keys[idx] < key) ++idx;
		return idx;
	}
	
	void BTreeNode::remove(int key)
	{
		int idx = findKey(key);
		
		if (idx < n && keys[idx] == key)
		{
			if (leaf) removeFromLeaf(idx);
			else removeFromNonLeaf(idx);
		}
		else
		{
			
			if (leaf)
			{
				cout << "The key " << key << " does not exist in the tree\n";
				return;
			}
			
			bool flag = ((idx == n) ? true : false);
			
			if (C[idx]->n < t)
				fill(idx);
			
			if (flag && idx > n) C[idx - 1]->remove(key);
			else C[idx]->remove(key);
		}
		return;
	}

	void BTreeNode::removeFromLeaf(int idx)
	{
		for (int i = idx + 1; i < n; ++i)
		{
			keys[i - 1] = keys[i];
		}

		n--;

		return;
	}

	void BTreeNode::removeFromNonLeaf(int idx)
	{
		int k = keys[idx];

		if (C[idx]->n >= t)
		{
			int pred = getPred(idx);
			keys[idx] = pred;
			C[idx]->remove(pred);
		}
		else if (C[idx + 1]->n >= t)
		{
			int succ = getSucc(idx);
			keys[idx] = succ;
			C[idx + 1]->remove(succ);
		}		
		else
		{
			merge(idx);
			C[idx]->remove(k);
		}
		return;
	}

	int BTreeNode::getPred(int idx)
	{	
		BTreeNode *cur = C[idx];
		while (!cur->leaf)
			cur = cur->C[cur->n];

		
		return cur->keys[cur->n - 1];
	}

	int BTreeNode::getSucc(int idx)
	{		
		BTreeNode *cur = C[idx + 1];
		while (!cur->leaf)
			cur = cur->C[0];
	
		return cur->keys[0];
	}

	void BTreeNode::fill(int idx)
	{
		if (idx != 0 && C[idx - 1]->n >= t)
			borrowFromPrev(idx);

		else if (idx != n && C[idx + 1]->n >= t)
			borrowFromNext(idx);
		
		else
		{
			if (idx != n) merge(idx);
			else merge(idx - 1);
		}

		return;
	}

	void BTreeNode::borrowFromPrev(int idx)
	{

		BTreeNode *child = C[idx];
		BTreeNode *sibling = C[idx - 1];		
		
		for (int i = child->n - 1; i >= 0; --i)
		{
			child->keys[i + 1] = child->keys[i];
		}
		
		if (!child->leaf)
		{
			for (int i = child->n; i >= 0; --i)
				child->C[i + 1] = child->C[i];
		}

		
		child->keys[0] = keys[idx - 1];	
		
		if (!leaf)
			child->C[0] = sibling->C[sibling->n];
		
		keys[idx - 1] = sibling->keys[sibling->n - 1];


		child->n += 1;
		sibling->n -= 1;

		return;
	}
	
	void BTreeNode::borrowFromNext(int idx)
	{
		BTreeNode * child = C[idx];
		BTreeNode * sibling = C[idx + 1];
		
		child->keys[(child->n)] = keys[idx];

		
		
		if (!(child->leaf))
			child->C[(child->n) + 1] = sibling->C[0];

		
		keys[idx] = sibling->keys[0];

		
		for (int i = 1; i < sibling->n; ++i)
			sibling->keys[i - 1] = sibling->keys[i];

		
		if (!sibling->leaf)
		{
			for (int i = 1; i <= sibling->n; ++i)
				sibling->C[i - 1] = sibling->C[i];
		}
		
		
		child->n += 1;
		sibling->n -= 1;

		return;
	}

	void BTreeNode::merge(int idx)
	{
		BTreeNode * child = C[idx];
		BTreeNode * sibling = C[idx + 1];
		
		child->keys[t - 1] = keys[idx];

		
		for (int i = 0; i < sibling->n; ++i)
			child->keys[i + t] = sibling->keys[i];

		
		if (!child->leaf)
		{
			for (int i = 0; i <= sibling->n; ++i)
				child->C[i + t] = sibling->C[i];
		}
		
		
		for (int i = idx + 1; i < n; ++i)
			keys[i - 1] = keys[i];

		
		
		for (int i = idx + 2; i <= n; ++i)
			C[i - 1] = C[i];

		
		child->n += sibling->n + 1;
		n--;


		delete(sibling);
		return;
	}


	template <typename T>
	class BTree
	{
		BTreeNode * root; 
		int t;
		SortedSequence<T> data;
	public:
		BTree(int _t) { root = nullptr;  t = _t; }
		void traverse() { if (root) root->traverse(data); }
		BTreeNode * search(int k) { return (root == nullptr) ? nullptr : root->search(k); }
		T getValue(int key) { return data.getValue(data.BinSearch(key)); }
		int operator [] (int k) { return root->find(k).key; }
		T operator () (int k) { return root->find(k).value; }
		void insert(int key, T value);
		void remove(int k);
		void Add();
		void Find();
		void Delete();
		bool IsEmpty() { bool b; root ? b = false : b = true; return b; }
	};

	template <typename T>
	void BTree<T>::Add()
	{
		cout << "Enter key and value:" << endl;
		int key;
		T value;

		getNum(key, 0, -1);
		cin >> value;
		insert(key, value);
	}
	
	template <typename T>
	void BTree<T>::Find()
	{
		cout << "Enter key:" << endl;
		int key;

		getNum(key, 0, -1);
		cout << search(key) << endl;
	}

	template <typename T>
	void BTree<T>::Delete()
	{
		cout << "Enter key:" << endl;
		int key;

		getNum(key, 0, -1);
		remove(key);
	}

	template <typename T>
	void BTree<T>::remove(int k)
	{
		if (!root)
		{
			cout << "The tree is empty\n";
			return;
		}

		root->remove(k);

		if (root->n == 0)
		{
			BTreeNode * tmp = root;
			if (root->leaf)
				root = NULL;
			else
				root = root->C[0];
			
			delete tmp;
			data.delelem(k);
		}
	}

	template <typename T>
	void BTree<T>::insert(int k, T value)
	{
		if (root == nullptr)
		{
			root = new BTreeNode(t, true);
			root->keys[0] = k;
			root->n = 1;
		}
		else 
		{
			if (root->n == 2 * t - 1)
			{
				BTreeNode * s = new BTreeNode(t, false);

				s->C[0] = root;

				s->splitChild(0, root);

				int i = 0;
				if (s->keys[0] < k) i++;
				s->C[i]->insertNonFull(k);

				root = s;
			}
			else
			{
				root->insertNonFull(k);
			}
		}
		data.addelem(k, value);
	}
}