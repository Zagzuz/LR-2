#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace student
{
	class Student
	{
	private:
		string Name;
		string Surname;
		string Group;
		int Age;
	public:
		Student() { Age = 0; }
		Student(string, string, string, int);
		Student(const Student &);
		void InitStudent();
		Student operator = (const Student &);
		friend ostream & operator << (ostream &, Student &);
		string getName() { return Name; }
		string getSurname() { return Surname; }
		string getGroup() { return Group; }
		int getAge() { return Age; }
		void changeGroup(string newGroup) { Group = newGroup; }
		void IncAge() { Age++; }
		int getID();
	};

	void Student::InitStudent()
	{
		if (Age)
		{
			cout << "Имя: ";
			cin >> Name;  cout << endl;
			cout << "Фамилия: ";
			cin >> Surname; cout << endl;
			cout << "Группа: ";
			cin >> Group; cout << endl;
			cout << "Возраст: ";
			cin >> Age; cout << endl;
		}
		else
		{
			cout << "Студент уже определен" << endl;
		}
	}

	Student Student::operator = (const Student &X)
	{
		Name = X.Name;
		Surname = X.Surname;
		Group = X.Group;
		Age = X.Age;
		return *this;
	}

	ostream & operator << (ostream &os, Student &X)
	{
		os << " | Имя: " << X.getName() << " | Фамилия: " << X.getSurname();
		os << " | Группа: " << X.getGroup() << " | Возраст: " << X.getAge() << " | " << endl;
		return os;
	}


	int Student::getID()
	{
		int id = 0, x;
		char buffer[3];
		errno = _itoa_s(21, buffer, 10);
		string info = getName() + getSurname() + getGroup() + buffer;
		
		for (size_t i = 0; i <= info.size(); i++)
		{
			x = info[i] - '0';
			if (x > 16 && x < 43 || x > 48 && x < 75 || info[i] <= '9' && info[i] >= '0')
				id += x * i;
			if (x > -113 && x < -50)
				id -= x * i;
		}

		return id;
	}

	Student::Student(string newName, string newSurname, string newGroup, int newAge)
	{
		Name = newName;
		Surname = newSurname;
		Group = newGroup;
		Age = newAge;
	}

	Student::Student(const Student &X)
	{
		Name = X.Name;
		Surname = X.Surname;
		Group = X.Group;
		Age = X.Age;
	}
}