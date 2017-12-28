#pragma once
#include "node.h"

template<typename T>
class list
{
public:
	node<T> * root;
	node<T> * tail;
	list() { root = new node<T>[sizeof(node<T>)]; tail = nullptr; /*конец указывает на null - лист пуст*/ }
	list<T> & operator = (const list<T> &);
};

template<typename T>
list<T> & list<T>::operator = (const list<T> &l)
{
	delete[] root;
	root = nullptr;
	tail = nullptr;

	root = new node<T>[sizeof(node<T>)];

	if(!l.tail) return *this;

	node<T> * a = root;
	node<T> * b = l.root;

	while (b)
	{
		if (b->next)
		{
			a->next = new node<T>[sizeof(node<T>)];
			a->next->prev = a;
			a->next->element = b->next->element;
			b = b->next;
			a = a->next;
		}
		else
		{
			tail = a;
			break;
		}
	}

	return *this;
}