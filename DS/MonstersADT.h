#pragma once

template <class T>
class MonstersADT {
	enum {MAX_SIZE = 1000};
	T arr[MAX_SIZE];
	int count;
public:
	MonstersADT();
	bool isEmpty();
	bool isFull();
	bool add(T val);
	bool remove(int idx);
	void print();
	T& operator [](int idx);
};

template<class T>
MonstersADT<T>::MonstersADT() {
	count = 0;
}

template<class T>
bool MonstersADT<T>::isEmpty() {
	return !count;
}

template<class T>
bool MonstersADT<T>::isFull() {
	return count >= 1000;
}

template<class T>
bool MonstersADT<T>::add(T val) {
	if (isFull()) return false;
	arr[count++] = val;
	return true;
}

template<class T>
bool MonstersADT<T>::remove(int idx) {
	if (idx > count - 1 || idx < 0) 
		return false;

	swap(arr[idx], arr[count - 1]);
	count--;
	return true;
}

template<class T>
void MonstersADT<T>::print() {
	if (isEmpty()) return;

	for (int i = 0; i < count - 1; i++)
		cout << arr[i] << ", ";
	cout << arr[count - 1];
}

template<class T>
T& MonstersADT<T>::operator[](int idx)
{
	return arr[idx];
}
