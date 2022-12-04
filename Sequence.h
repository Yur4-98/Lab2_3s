#pragma once

#include "Complex.h"
#include "DynamicArray.h"
#include "LinkedList.h"
using namespace std;

template < typename T>
class Sequence
{
protected:
	//	Sequence(int size);
	//	Sequence(int size, T def);
	//	Sequence();
	//	Sequence(T* items, int count);
	//	Sequence(const Sequence<T>& sequence);

public:

	virtual ~Sequence() = 0;

	virtual T GetFirst() = 0;
	virtual T GetLast() = 0;
	virtual T Get(int index) = 0;
	virtual int GetSize() = 0;

	virtual void InsertAt(int index, T item) = 0;
	virtual void Append(T value) = 0;
	virtual void Prepend(T value) = 0;
	virtual void Resize(int newsize) = 0;

	virtual T& operator[](int index) = 0;

	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
	virtual Sequence <T>* Concat(Sequence<T>* list) = 0;
};

template<typename T>
Sequence<T>::~Sequence() {}


template<typename T>
class ArraySequence : public Sequence<T>
{
private:
	DynamicArray<T> items;
public:
	ArraySequence();
	ArraySequence(const ArraySequence<T>& arraySequence);
	ArraySequence(T* items, int count);
	ArraySequence(int size);
	ArraySequence(int size, T def);
	~ArraySequence() override;

	T GetFirst() override;
	T GetLast() override;
	T Get(int index) override;
	int GetSize() override;

	void InsertAt(int index, T item) override;
	void Append(T item) override;
	void Prepend(T item) override;
	void Resize(int newsize) override;

	void DelEnd();

	T& operator[](int index) override;
	void operator= (ArraySequence<T> array);

	ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) override;
	ArraySequence<T>* Concat(Sequence <T>* list);
};

template<typename T>
void ArraySequence<T>::operator=(ArraySequence<T> array) {
	this->items = array.items;

}

template<typename T>
ArraySequence<T>::ArraySequence()
{
	this->items = DynamicArray<T>();
}

template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& arraySequence)
{
	this->items = DynamicArray<T>/* items*/(arraySequence.items);
}

template<typename T>
ArraySequence<T>::ArraySequence(T* items, int size)
{
	this->items = DynamicArray<T>(items, size);
}

template<typename T>
ArraySequence<T>::ArraySequence(int size)
{
	this->items = DynamicArray<T>/* items*/(size);
}

template<typename T>
ArraySequence<T>::ArraySequence(int size, T def)
{
	this->items = DynamicArray<T>/* items*/(size, def);
}

template<typename T>
ArraySequence<T>::~ArraySequence()
{

}




template<typename T>
T& ArraySequence<T>::operator[](int index) {
	return this->items[index];
}

template<typename T>
T ArraySequence<T>::GetFirst() {
	return (this->items).GetFirst();
}

template<typename T>
T ArraySequence<T>::GetLast() {
	return this->items.GetLast();
}

template<typename T>
T ArraySequence<T>::Get(int index) {
	return this->items.Get(index);
}

template<typename T>
int ArraySequence<T>::GetSize() {
	return this->items.GetSize();
}

template<typename T>
void ArraySequence<T>::InsertAt(int index, T item) {
	this->items.Set(index, item);
}

template<typename T>
void ArraySequence<T>::Append(T item) {
	this->items.Append(item);
}

template<typename T>
void ArraySequence<T>::DelEnd() {
	this->items.DelEnd();
}

template<typename T>
void ArraySequence<T>::Prepend(T item) {
	this->items.Prepand(item);
}

template<typename T>
void ArraySequence<T>::Resize(int newsize)
{
	this->items.Resize(newsize);
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) {
	ArraySequence<T>* list1 = static_cast<ArraySequence<T>*>(list);
	ArraySequence<T>* newArraySequence = new ArraySequence<T>(this->GetSize() + list1->GetSize());

	newArraySequence->items = *(this->items.Concat(&list1->items));
	return newArraySequence;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) {
	ArraySequence<T>* newArraySequence = new ArraySequence<T>;
	*newArraySequence = ArraySequence<T>(endIndex - startIndex + 1);
	newArraySequence->items = *this->items.GetSubarray(startIndex, endIndex);
	return newArraySequence;
}

template<typename T>
class ListSequence : public Sequence<T>
{
private:
	LinkedList<T> items;
public:
	ListSequence();
	ListSequence(const ListSequence<T>& ListSequence);
	ListSequence(T* items, int count);

	~ListSequence() override;

	T GetFirst() override;
	T GetLast() override;
	T Get(int index) override;
	int GetSize() override;

	void InsertAt(int index, T item) override;
	void Append(T item) override;
	void Prepend(T item) override;
	void Resize(int newsize) override {};

	T& operator[](int index) override;
	void operator= (ListSequence<T> array);

	ListSequence<T>* GetSubsequence(int startIndex, int endIndex) override;
	ListSequence<T>* Concat(Sequence <T>* list);
};


template<typename T>
void ListSequence<T>::operator=(ListSequence<T> list) {
	this->items = list.items;

}

int numbers[1] = {};//
template<typename T>
ListSequence<T>::ListSequence()
{
	this->items = LinkedList<T>(numbers, 0);//
}

template<typename T>
ListSequence<T>::ListSequence(const ListSequence<T>& ListSequence)
{
	this->items = LinkedList<T>(ListSequence.items);
}

template<typename T>
ListSequence<T>::ListSequence(T* items, int count)
{
	this->items = LinkedList<T>(items, count);
}

template<typename T>
ListSequence<T>::~ListSequence()
{
	//	delete &(this->items);
}




template<typename T>
T& ListSequence<T>::operator[](int index) {
	return this->items[index];
}

template<typename T>
T ListSequence<T>::GetFirst() {
	return (this->items).GetFirst();
}

template<typename T>
T ListSequence<T>::GetLast() {
	return this->items.GetLast();
}

template<typename T>
T ListSequence<T>::Get(int index) {
	return this->items.Get(index);
}

template<typename T>
int ListSequence<T>::GetSize() {
	return this->items.GetSize();
}

template<typename T>
void ListSequence<T>::InsertAt(int index, T item) {
	this->items.InsertAt(item, index);
}

template<typename T>
void ListSequence<T>::Append(T item) {
	(this->items).Append(item);
}

template<typename T>
void ListSequence<T>::Prepend(T item) {
	this->items.Prepend(item);
}



template<typename T>
ListSequence<T>* ListSequence<T>::Concat(Sequence<T>* list) {
	ListSequence<T>* list1 = static_cast<ListSequence<T>*>(list);
	ListSequence<T>* newListSequence = new ListSequence<T>();

	newListSequence->items = *(this->items.Concat(&(list1->items)));
	return newListSequence;
}

template<typename T>
ListSequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) {
	ListSequence<T>* newListSequence = new ListSequence<T>;
	//	for (int i = 0; i < endIndex - startIndex + 1; i++)
	//	{
	//		newListSequence->Append(this->items[i]);
	//	}
	newListSequence->items = *this->items.GetSubList(startIndex, endIndex);
	return newListSequence;
}

