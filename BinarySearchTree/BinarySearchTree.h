#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Student.h"
#include "SortedSequence.h"

using namespace std;
using namespace student;
using namespace sortedsequence;

namespace binarysearchtree
{
	template <typename T>
	class BinarySearchTree
	{
	private:
		struct node
		{
			int key;
			node * r;
			node * l;
			node() { r = nullptr; l = nullptr; key = 0; }
		};
		node * cur;
		node * root;
		SortedSequence<T> data;
	public:
		BinarySearchTree() { cur = new node[sizeof(node)]; root = cur; }
		~BinarySearchTree() { delete[] cur; cur = nullptr; root = nullptr; }
		T getValue(int key) { return data.getValue(data.BinSearch(key)); }
		int add_element(int, T);
		node * deleteNode(node *, int);
		void delete_element(int key) { cur = root; node * temp = deleteNode(cur, key); data.delelem(key); if (data.getLength() == 1) cur = root = temp; else cur = temp; }
		bool IsEmpty() { bool b; root->key == 0 ? b = true : b = false; return b; }
		node * search_element(int);
		void print_node(node * p, int indent);
		void print_tree() { int indent = rootlnum() * 5; cur = root; print_node(cur, indent); cur = root; };
		int rootlnum() { int x = 0; cur = root; do { if (cur->l) { cur = cur->l; x++; } else break; } while (cur->l); cur = root; return x; }
		node * FindMin(node *);
	};

	template <typename T>
	void BinarySearchTree<T>::print_node(node * p, int indent)
	{
		if (p)
		{
			if (p->l) print_node(p->l, indent - 5);
			if (p->r) print_node(p->r, indent + 5);
			if (indent)
				std::cout << std::setw(indent) << ' ';
			cout << p->key << "\n ";
		}
	}

	template <typename T>
	typename BinarySearchTree<T>::node * BinarySearchTree<T>::FindMin(typename BinarySearchTree<T>::node * r) {

		typename BinarySearchTree<T>::node *temp = r;
		while (temp->l)
			temp = temp->l;
		return temp;
	}

	template<typename T>
	typename BinarySearchTree<T>::node * BinarySearchTree<T>::deleteNode(typename BinarySearchTree<T>::node * cur, int key)
	{
		if (key == root->key && !root->r && !root->l)
		{
			root->key = 0;
			return root;
		}

		if (key < cur->key)
			cur->l = deleteNode(cur->l, key);
		else if (key > cur->key)
			cur->r = deleteNode(cur->r, key);
		else
		{
			if (!cur->l)
			{
				typename BinarySearchTree<T>::node * temp = cur->r;
				delete[] cur;
				cur = nullptr;
				return temp;
			}
			else if (!cur->r)
			{
				typename BinarySearchTree<T>::node * temp = cur->l;
				delete[] cur;
				cur = nullptr;
				return temp;
			}

			typename BinarySearchTree<T>::node * temp = FindMin(cur->r);

			cur->key = temp->key;
			
			cur->r = deleteNode(cur->r, temp->key);
		}

		return cur;
	}

	template <typename T>
	int BinarySearchTree<T>::add_element(int key, T value)
	{
		if (IsEmpty())
		{
			cur->key = key;
			data.addelem(key, value);
			return 1;
		}

		while (cur)
		{
			if (key == cur->key)
			{
				data.rewrite(key, value);
				return 1;
			}
			else if (key > cur->key)
			{
				if (cur->r) cur = cur->r;
				else
				{
					cur->r = new node[sizeof(node)];
					cur = cur->r;
					cur->key = key;
					data.addelem(key, value);
					cur = root;
					return 1;
				}
			}
			else if (key < cur->key)
			{
				if (cur->l) cur = cur->l;
				else
				{
					cur->l = new node[sizeof(node)];
					cur = cur->l;
					cur->key = key;
					data.addelem(key, value);
					cur = root;
					return 1;
				}
			}
		}

		return 0;
	}

	template <typename T>
	typename BinarySearchTree<T>::node * BinarySearchTree<T>::search_element(int key)
	{
		cur = root;

		while (cur)
		{
			if (cur->key == key)
			{
				return cur;
			}
			else if (key > cur->key)
			{
				if (cur->r) cur = cur->r; else break;
			}
			else if (key < cur->key)
			{
				if (cur->l) cur = cur->l; else break;
			}
		}

		return nullptr;
	}
}

