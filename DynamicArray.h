#pragma once
#include <iostream>
#include "Complex.h"

using namespace std;
template <typename T>
class DynamicArray
{
private:
	T* array;
	int size;

	//errors
	const int ERROR_INDEX_OUT_OF_RANGE = 1;
	const int ERROR_INVALID_SIZE = 2;
public:
	DynamicArray();
	DynamicArray(T* items, int count);
	DynamicArray(int size);
	DynamicArray(int size, T def);
	DynamicArray(const DynamicArray<T>& dynamicArray);

	~DynamicArray();

	T Get(int index);
	int GetSize();
	T GetFirst();
	T GetLast();

	void Set(int index, T value);
	void Resize(int newSize);
	//void InsertAt(T value, int index);
	//void Erase(int index);
	void Append(T item);
	void Prepand(T item);
	void DelEnd();

	T& operator[](int index);
	void operator= (DynamicArray<T> array);
	//bool operator== (DynamicArray<T>& a);
	//bool operator!= (DynamicArray<T>& a);

	DynamicArray<T>* Concat(DynamicArray<T>* list);
	DynamicArray<T>* GetSubarray(int startIndex, int endIndex);
};

template<typename T>
void DynamicArray<T>::operator=(DynamicArray<T> array) {
	this->size = array.size;
	this->array = array.array;
}

template<typename T>
DynamicArray<T>* DynamicArray<T>::Concat(DynamicArray<T>* list) {
	DynamicArray<T>* newArray = new DynamicArray<T>();
	for (int i = 0; i < this->size; i++)
	{
		newArray->Append(this->array[i]);
	}
	for (int i = 0; i < list->size; i++)
	{
		newArray->Append(list->array[i]);
	}
	return newArray;

}

template<typename T>
DynamicArray<T>* DynamicArray<T>::GetSubarray(int startIndex, int endIndex) {
	DynamicArray<T>* newArray = new DynamicArray<T>;
	*newArray = DynamicArray<T>(endIndex - startIndex + 1);
	int a = 0;

	for (int i = startIndex; i <= endIndex; i++)
	{
		(*newArray)[a] = this->array[i];
		a++;
	}
	return newArray;
}

template<typename T>
void DynamicArray<T>::Append(T item) {
	(*this).Resize((this->size + 1));
	this->array[size - 1] = item;
}

template<typename T>
void DynamicArray<T>::DelEnd() {
	(*this).Resize((this->size - 1));
}

template<typename T>
void DynamicArray<T>::Prepand(T item) {
	(*this).Resize(this->size + 1);
	for (int i = this->size - 1; i > 0; i--)
	{
		this->array[i] = this->array[i - 1];
	}
	this->array[0] = item;
}

template <typename T>
T DynamicArray<T>::GetLast() {
	return DynamicArray<T>::array[DynamicArray<T>::size - 1];
}

template <typename T>
T DynamicArray<T>::GetFirst() {
	return DynamicArray<T>::array[0];
}

template <typename T>
DynamicArray<T>::DynamicArray() {
	this->size = 0;
	this->array = 0;
}
//
template <typename T>
DynamicArray<T>::DynamicArray(int size) {
	this->size = size;
	this->array = new T[size];
	for (int i = 0; i < size; i++)
	{
		this->array[i] = T();
	}
}
//
template <typename T>
DynamicArray<T>::DynamicArray(int size, T def) {
	this->size = size;
	this->array = new T[size];
	for (int i = 0; i < size; i++)
	{
		this->array[i] = T(def);
	}
}

template <typename T>
DynamicArray<T>::DynamicArray(T* items, int size) {
	this->size = size;
	if (!size) {
		this->array = 0;
		return;
	}
	this->array = new T[size];
	for (int i = 0; i < size; i++)
	{
		this->array[i] = items[i];
	}
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) {

	this->size = dynamicArray.size;
	this->array = new T[dynamicArray.size];
	for (int i = 0; i < dynamicArray.size; i++)
	{
		this->array[i] = dynamicArray.array[i];
	}


}



template <typename T>
DynamicArray<T>::~DynamicArray() {

}

template <typename T>
T DynamicArray<T>::Get(int index) {
	if (index < 0 || index >= this->size)
	{
		throw ERROR_INDEX_OUT_OF_RANGE;
	}
	return DynamicArray<T>::array[index];
}

template <typename T>
int DynamicArray<T>::GetSize() {
	return DynamicArray<T>::size;
}

template <typename T>
void DynamicArray<T>::Set(int index, T value) {
	if (index < 0 || index > this->size)
	{
		throw ERROR_INDEX_OUT_OF_RANGE;
	}
	DynamicArray<T>::array[index] = value;
}

template <typename T>
void DynamicArray<T>::Resize(int newSize) {
	if (newSize < 0)
	{
		throw ERROR_INVALID_SIZE;
		return;
	}
	T* tmp = new T[newSize];
	for (int i = 0; i < this->size && i < newSize; i++)
	{
		tmp[i] = this->array[i];
	}
	delete[] this->array;
	this->array = tmp;
	this->size = newSize;

}

template <typename T>
T& DynamicArray<T>::operator[](int index) {
	return this->array[index];
}
