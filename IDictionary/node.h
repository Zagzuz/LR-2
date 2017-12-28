#pragma once

#include "datatype.h"

template<typename T>
class node
{
public:
	datatype<T> element;
	node<T> * prev;
	node<T> * next;
	node() { element.setKey(0); next = nullptr; prev = nullptr; }
	node(datatype<T> a) { element = a; next = nullptr; prev = nullptr; }
	node(int initkey, T initvalue) { element.setKey(initkey); element.setValue(initvalue); next = nullptr; prev = nullptr; }
	node<T> * nextNode() { return x->next; }
	node<T> * prevNode() { return x->prev; }
	datatype<T> getElement() { return element; }
	void setNodeKey(int key) { element.setKey(key); }
	void setNodeValue(T value) { element.setValue(value); }
};

