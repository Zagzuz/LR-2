#pragma once
#include <iostream>

using namespace std;

namespace srtseq
{
	template <typename T>
	class SortedSequence
	{
	private:
		struct node
		{
			T value;
			int key, version;
			node * next;
			node * prev;
			node() { key = -1; version = 0; next = nullptr; prev = nullptr; }
		};
		struct element
		{
			node * root;
			node * tail;
			node * cur;
			int k;
			element() { root = cur = nullptr; tail = nullptr; k = 0; }
			element operator = (element a);
			element operator ~();
		};
		element * arr;
		int len, quan;
	public:
		SortedSequence() { quan = 1; len = 0; }
		~SortedSequence() { if (len != 0) { for (int i = 0; i < quan; i++) ~arr[i];  delete[] arr; } }
		int hash(int key) { return key % quan; }
		int add_element(int, T);
		int delete_element(int, int);
		typename SortedSequence<T>::node * find_element(int, int);
		void expand_table();
		void Add();
		void Delete();
		void Search();
	};

	template <typename T>
	typename SortedSequence<T>::element SortedSequence<T>::element::operator ~ ()
	{
		while (cur)	//если в этом элементе есть список
		{
			if (cur->next)
			{
				cur = cur->next;
				delete[] cur->prev;
				cur->prev = nullptr;
			}
			else
			{
				delete[] cur;
				cur = nullptr;
				break;
			}
		}

		return *this;
	}

	template <typename T>
	typename SortedSequence<T>::element SortedSequence<T>::element::operator = (element a)
	{
		~*this;

		element tmp;
		tmp.cur = new node[sizeof(node)];
		tmp.root = tmp.cur;
		tmp.tail = tmp.cur;

		//a.cur = a.root;

		while (a.cur)	//идем по списку значений этого элемента
		{
			if (tmp.tail == tmp.root)	//если это первый элемент
			{
				tmp.tail->key = a.cur->key;	//вставляем сюда ключ
				tmp.tail->value = a.cur->value;	//и значение
				tmp.tail->version = 1; //версия - 1
			}
			else	//если tail != root
			{
				tmp.tail->next = new node[sizeof(node)];
				tmp.tail->next->key = a.cur->key;	//вставляем в новый конец списка ключ
				tmp.tail->next->value = a.cur->value;	//и значение
				tmp.tail->next->version = tmp.tail->version;
				tmp.tail->next->prev = tmp.tail;
			}

			if (a.cur->next)	// если в списке есть следующее знчение
			{
				if (tmp.tail != tmp.root)	//если хвост не совпадает с началом
					tmp.tail = tmp.tail->next;	//переходим к след к arr.tail
				a.cur = a.cur->next;	//переходим к след в a.cur
			}
			else	//если это было последнее значение списка a.cur = a.tail
			{
				a.cur = a.root;	//возвращаем указатель a.cur в начало

				break;	//выходим
			}
		}

		return tmp;
	}

	template<typename T>
	typename SortedSequence<T>::node * SortedSequence<T>::find_element(int key, int version)
	{
		int pos = hash(key);
		SortedSequence<T>::node * a = arr[pos].cur;

		if (!arr[pos].tail) return nullptr;
		if (arr[pos].tail->version == 1) return arr[pos].tail;

		while (arr[pos].cur)
		{
			if (arr[pos].cur->version == version) { a = arr[pos].cur; return a; }
			if (arr[pos].cur->next) arr[pos].cur = arr[pos].cur->next; else break;
		}

		return nullptr;
	}

	template<typename T>
	void SortedSequence<T>::Search()
	{
		SortedSequence<T>::node * a = find_element(key, version);
		return a->value;
	}

	template <typename T>
	void SortedSequence<T>::Add()
	{
		cout << "Enter element key: " << endl;
		int key;
		cin >> key;

		cout << "Enter element value: " << endl;
		T value;
		cin >> value;

		if (key <= 0) { throw exception("invalid key"); return; }

		add_element(key, value);
	}

	template <typename T>
	void SortedSequence<T>::Delete()
	{

	}

	template <typename T>
	void SortedSequence<T>::expand_table()
	{
		if (quan == len)
			quan *= 2;

		element * tmp = new element[quan];

		

	/*	int i = 0;

		while (i < len)
		{
			for (int j = 0; j < quan / 2; j++)
			{

			}
		}
		*/









			/*if (arr[i].root)	//если этот на этом месте есть список
			{
				while (arr[i].cur)	//идем по списку элементов этого места в массиве
				{
					tmp[hash(arr[i].cur->key)].tail->next->key = arr[i].cur->key;	//вставляем в конец tmp ключ

					tmp[hash(arr[i].cur->key)].tail->next->value = arr[i].cur->value;	//и значение

					if (tmp[hash(arr[i].cur->key)].cur != tmp[hash(arr[i].cur->key)].root)	//если это не первый эл-т
					{
						tmp[hash(arr[i].cur->key)].tail->version = tmp[hash(arr[i].cur->key)].tail->prev->version;	//версия этого эл-та равна версии предыдущего + 1
					}
					else
					{
						tmp[hash(arr[i].cur->key)].tail->version = 1;	//если это первый, то версия равна 1
					}

					if (arr[i].cur->next)	// если в списке есть следующий эл-т
					{
						tmp[hash(arr[i].cur->key)].tail->next = new node[sizeof(node)];	//создаем следующий для tmp.tail

						tmp[hash(arr[i].cur->key)].tail->next->prev = tmp[hash(arr[i].cur->key)].tail;	//tmp.tail->next->prev = tmp;

						tmp[hash(arr[i].cur->key)].tail = tmp[hash(arr[i].cur->key)].tail->next;	//переходим к след к tmp.tail

						arr[i].cur = arr[i].cur->next;	//переходим к след в arr[i].cur
					}
					else
					{
						arr[i].cur = arr[i].root;	//возвращаем указатель arr[i].cur в начало

						break;	//выходим
					}
				}
			}
		}	//скопировали все из arr в tmp;
		*/

		for (int i = 0; i < quan; i++) 
			if (arr[i].cur) ~arr[i]; 
		delete[] arr;

		arr = new element[quan];

		for (int i = 0; i < quan; i++)
			if (arr[i].cur) arr[i] = tmp[i];

		len++;
	}

	template<typename T>
	int SortedSequence<T>::add_element(int key, T value)
	{
		if (len == 0)
		{
			arr = new element[quan];
			arr[0].cur = new node[sizeof(node)];
			arr[0].tail = arr[0].cur;
			arr[0].root = arr[0].cur;
			arr[0].cur->key = key;
			arr[0].cur->value = value;
			arr[0].cur->version = 1;
			len++;
			return 1;
		}

		expand_table();

		int pos = hash(key);

		if (find_element(key, 1))
		{
			arr[pos].tail->next = new node[sizeof(node)];
			arr[pos].tail->next->prev = arr[pos].tail;
			arr[pos].tail = arr[pos].tail->next;
			arr[pos].tail->value = value;
			arr[pos].tail->key = key;
			arr[pos].tail->version = arr[pos].tail->prev->version;
			return 1;
		}
		else
		{
			arr[pos].cur = new node[sizeof(node)];
			arr[pos].cur->value = value;
			arr[pos].cur->key = key;
			arr[pos].cur->version = 1;
			arr[pos].tail = arr[pos].cur;
			return 1;
		}
		return 0;
	}

	template <typename T>
	int SortedSequence<T>::delete_element(int key, int version)
	{
		if (exists(key))
		{
			int pos = hash(key);
			while (arr[pos].cur)
			{
				if (arr[pos].tail = arr[pos].root)
				{
					arr[pos].tail->key = -1;
					arr[pos].tail->version = 0;
					arr[pos].tail = nullptr;
				}
				else
				{
					while (arr[pos].cur)
					{
						if (arr[pos].cur->value == value)

						else if (arr[pos].cur != arr[pos].tail)
						{
							arr[pos].cur->next->prev = arr[pos].cur->prev;
							arr[pos].cur->prev->next = arr[pos].cur->next;
							delete[] arr[pos].cur;
							arr[pos].cur = nullptr;
							arr[pos].cur = root;
						}
						else
						{
							delete[] arr[pos].cur;
							arr[pos].cur->next  nullptr;
						}
					}
					if (arr[pos].cur->next) arr[pos].cur = arr[pos].cur->next;
				}
			}
		}
		return 0;
	}
}