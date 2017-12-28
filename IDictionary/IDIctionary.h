#pragma once

#include <iostream>
#include "list.h"

using namespace std;

namespace idictionary
{
	template <typename T>
	class IDictionary
	{
	private:
		list<T> * array;/*массив списков*/
		int count;/*количество непустых списков массива*/
		int capacity;/*размер массива списков*/
	public:
		IDictionary();
		IDictionary(const IDictionary<T> &);
		~IDictionary();
		IDictionary<T> & operator = (const IDictionary<T> &);
		int GetCount() { return count; }
		int GetCapacity() { return capacity; }
		void add(int key, T value);
		void add(datatype<T> el);
		IDictionary<T> & extend();
		node<T> * search(int);/*возвращает указатель на последний элемент в списке с данным ключом*/
		T returnelem(int);/*возвращает первый элемент с данным ключом*/
		void showSimiliar(int);/*показывает все элементы с одним ключом*/
		int hash(int key) { return key % capacity; }
		template <typename T> friend class list;
	};

	template<typename T>
	IDictionary<T>::IDictionary()
	{ 
		count = 0; 
		capacity = 1;
		array = new list<T>[count];
	}

	template<typename T>
	void idictionary::IDictionary<T>::showSimiliar(int key)
	{
		int index = hash(key);

		if (array[index].tail)//список не пуст
		{
			node<T> * a = array[index].root;
			do
			{
				cout << a->element.getValue() << endl;
				if (a->next) a = a->next; else break;
			} while (a->next);
		}
	}

	template<typename T>
	node<T> * IDictionary<T>::search(int key)
	{
		int index = hash(key);

		if (index < count)//список не пуст
		{
			node<T> * a = array[index].root;
			do
			{
				if (a->next)
					if (a->next->element.getKey() == key) a = a->next;//это не последний элемент с таким ключом в списке
					else return a;//последний
			} while (a->next);
		}

		return nullptr;
	}

	template<typename T>
	T IDictionary<T>::returnelem(int key)
	{
		int index = hash(key);

		if (index < count)//список не пуст
			return array[index].root->element.getValue();

		return T();
	}

	template <typename T>
	IDictionary<T> & IDictionary<T>::operator = (const IDictionary<T> &A)
	{
		for (int i = 0; i < capacity; i++)
		{
			delete[] array[i].root;
			array[i].tail = nullptr;
			array[i].root = nullptr;
		}

		for (int i = 0; i < capacity; i++)
		{
			array[i] = A.array[i];
		}

		count = A.count;
		capacity = A.capacity;

		return *this;
	}

	template<typename T>
	void IDictionary<T>::add(int key, T value)
	{
		extend();

		if (count == 0)
		{
			array[0].root = new node<T>[sizeof(node<T>)];
			array[0].tail = array[0].root;
			array[0].root->element.setKey(key);
			array[0].root->element.setValue(value);
			count++;
			return;
		}

		int index = hash(key);
		node<T> * a = search(key);
		
		if (a)
		{
			if (a->next)//���� ����� ���� ���� �����-�� ������� (��� � ������ ������)
			{
				node<T> * tmp = new node<T>[sizeof(node<T>)];
				tmp->element.setKey(key);
				tmp->element.setValue(value);
				tmp->next = a->next;
				tmp->prev = a;
				a->next->prev = tmp;
				a->next = tmp;
				return;
			}
			else//���� �� ��������� � ������
			{
				a->next = new node<T>[sizeof(node<T>)];
				a->next->prev = a;
				a->next->element.setKey(key);
				a->next->element.setValue(value);
				array[index].tail = a->next;
				return;
			}
		}
		else
		{
			array[index].root = new node<T>[sizeof(node<T>)];
			array[index].root->element.setKey(key);
			array[index].root->element.setValue(value);
			array[index].tail = array[index].root;
			count++;
			return;
		}

		if (array[index].tail == array[index].root)//���� � ���� ������ ������ 1 �������
		{
			array[index].root->next = new node<T>[sizeof(node<T>)];
			array[index].root->next->element.setKey(key);
			array[index].root->next->element.setValue(value);
			array[index].root->next->prev = array[index].root;
			array[index].tail = array[index].root->next;
			return;
		}
	}

	template<typename T>
	void IDictionary<T>::add(datatype<T> el)
	{
		*this = extend();

		if (count == 0)
		{
			array[0].root = new node<T>[sizeof(node<T>)];
			array[0].tail = array[0].root;
			array[0].root->element = el;
			return;
		}

		int index = hash(el.getKey());
		node<T> * a = search(el.getKey());

		if (a)
		{
			if (a->next)//���� ����� ���� ���� �����-�� ������� (��� � ������ ������)
			{
				node<T> * tmp = new node<T>[sizeof(node<T>)];
				tmp->element = el;
				tmp->next = a->next;
				tmp->prev = a;
				a->next->prev = tmp;
				a->next = tmp;
				return;
			}
			else//���� �� ��������� � ������
			{
				a->next = new node<T>[sizeof(node<T>)];
				a->next->prev = a;
				a->next->element = el;
				array[index].tail = a->next;
				return;
			}
		}

		if (!array[index].tail)//���� ����
		{
			array[index].root->element = el;
			array[index].tail = array[index].root;
			count++;
			return;
		}

		if (array[index].tail == array[index].root)//���� � ���� ������ ������ 1 �������
		{
			array[index].root->next = new node<T>[sizeof(node<T>)];
			array[index].root->next->element = el;
			array[index].root->next->prev = array[index].root;
			array[index].tail = array[index].root->next;
			return;
		}
	}

	template <typename T>
	IDictionary<T> & IDictionary<T>::extend()
	{
		if (count == 0)
		{
			array = new list<T>[capacity];
			return *this;
		}

		if (capacity == count)
			capacity *= 2;

		IDictionary<T> TM;
		TM.array = new list<T>[capacity];

		node<T> * a;

		for (int i = 0; i < count; i++)
		{
			if (!array[i].tail) continue;
			a = array[i].root;
			while (a)
			{
				TM.add(a->element);
				if (a->next) a = a->next;
				else break;
			}
		}

		return TM;
	}
	

	template <typename T>
	IDictionary<T>::~IDictionary()
	{
		for (int i = 0; i < capacity; i++)
		{
			delete[] array[i].root;
			array[i].tail = nullptr;
			array[i].root = nullptr;
		}
		count = 0;
		capacity = 1; 
	}

	template <typename T>
	IDictionary<T>::IDictionary(const IDictionary<T> &A)
	{
		for (int i = 0; i < capacity; i++)
		{
			delete[] array[i].root;
			array[i].tail = nullptr;
			array[i].root = nullptr;
		}

		for (int i = 0; i < capacity; i++)
		{
			array[i] = A.array[i];
		}

		count = A.count;
		capacity = A.capacity;
	}

}