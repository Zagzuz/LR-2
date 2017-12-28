#pragma once

using namespace std;

template<typename T>
class datatype
{
private:
	T value;
	int key;
public:
	datatype() { key = 0; }
	datatype(int initkey, T initvalue) { key = initkey; value = initvalue; }
	datatype<T> & operator = (const datatype<T> &a) { value = a.value; key = a.key; return *this; }
	bool & operator == (datatype selement) { key == selement.key && value == selement.value ? return true : return false; }
	friend ostream& operator << (ostream&, const datatype<T> &);
	int getKey() { return key; }
	void setKey(int new_key) { key = new_key; }
	T getValue() { return value; }
	void setValue(T new_value) { value = new_value; }
};

template <typename T>
ostream & operator << (ostream &, const datatype<T>&e)
{
	cout << "key: " << e.getKey() << '\t' << "value: " << e.getValue();
	return ostream;
}