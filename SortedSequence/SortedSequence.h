#pragma once

#include <iostream>  
#include <locale.h>  
#include <conio.h>   
#include <algorithm> 

using namespace std;

namespace sortedsequence
{
	template <typename T>
	class SortedSequence
	{
	private:
		struct DataType
		{
			int key;
			T value;
			DataType() { key = 0; }
			DataType operator = (const DataType &a) { key = a.key; value = a.value; return *this; }
		};
		int size;
		DataType * arr;
	public:
		SortedSequence();
		SortedSequence(const SortedSequence<T> &);
		~SortedSequence();
		int getLength() { return size; }
		int getKey(int index) { return arr[index].key; }
		int BinSearch(int);
		void rewrite(int, T);
		void addelem(int, T);
		void delelem(int);
		SortedSequence<T> & operator ~ ();
		SortedSequence<T> operator = (const SortedSequence<T> &);
		T operator [] (int key) { return getValue(BinSearch(key)); }
		T getValue(int index) { if (index < 0 || index >= size) return T(); else return arr[index].value; }
		T keygetValue(int key) { return arr[BinSearch(key)].value; }
		template <typename T> friend ostream& operator << (ostream&, SortedSequence<T> &);
	};

	template <typename T>
	int getNum(T &a, int min, int max)
	{
		while (1)
		{
			cin >> a;
			if (cin.good() && (a >= min && a <= max || min == max || max < min && a > min))
			{
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cout << "Ќеправильный ввод: " << std::endl;
			cin.ignore(10, '\n');
		}
		return 0;
	}

	template <typename T>
	SortedSequence<T>::SortedSequence()
	{
		size = 0;
		arr = new DataType[size];
	}

	template <typename T>
	SortedSequence<T>::SortedSequence(const SortedSequence<T> &A)
	{
			delete[] arr;
			arr = new DataType[sizeof(A.size)];
	
		size = A.size;

		for (int i = 0; i < size; i++)
			arr[i] = A.arr[i];
	}

	template <typename T>
	SortedSequence<T>::~SortedSequence()
	{
		size = 0;
		delete[] arr;
	}

	template <typename T>
	SortedSequence<T> & SortedSequence<T>::operator ~ ()
	{
		delete[] arr;
		size = 0;
		arr = new DataType[size];
		return *this;
	}

	template <typename T>
	ostream& operator << (ostream& os, SortedSequence<T>& A)
	{
		for (int i = 0; i < A.getLength(); i++)
			os << A.getKey(i) << '\t' << A.getValue(i) << "\n";
		return os;
	}

	template <typename T>
	SortedSequence<T> SortedSequence<T>::operator = (const SortedSequence<T> &B)
	{
		delete[] arr;

		arr = new DataType[size = B.size];

		for (int i = 0; i < size; i++)
			arr[i] = B.arr[i];
		
		return *this;
	}

	template <typename T>
	int SortedSequence<T>::BinSearch(int key)
	{
		int l = 0;            // нижн€€ граница
		int u = size - 1;    // верхн€€ граница

		while (l <= u) 
		{
			int m = (l + u) / 2;
			if (arr[m].key == key) return m;
			if (arr[m].key < key) l = m + 1;
			if (arr[m].key > key) u = m - 1;
		}

		return -1;
	}

	template <typename T>
	void SortedSequence<T>::addelem(int key, T value)
	{
		DataType * x = new DataType[size + 1];

		for (int i = 0; i < size; i++)
		{
			x[i].key = arr[i].key;
			x[i].value = arr[i].value;
		}

		x[size].key = key;
		x[size].value = value;

		arr = x;

		size++;

		sort(arr, arr + size, [](DataType lhs, DataType rhs) { return lhs.key < rhs.key; });
	}

	template <typename T>
	void SortedSequence<T>::delelem(int k)
	{
		int pos = BinSearch(k);
		
		swap(arr[pos], arr[size - 1]);
		
		size--;
		
		if (size) sort(arr, arr + size, [](DataType lhs, DataType rhs) { return lhs.key < rhs.key; });
	}

	template <typename T>
	void SortedSequence<T>::rewrite(int key, T value)
	{
		int pos = BinSearch(key);

		arr[pos].value = value;
	}
}