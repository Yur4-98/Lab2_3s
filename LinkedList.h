#pragma once
#include <iostream>
#include <cmath>
#include "Complex.h"

using namespace std;

template <typename T>
struct LinkedListItem
{
	//private:
	T item;
	LinkedListItem<T>* next;
	//	LinkedListItem<T>* prev;
	//public:
	//	LinkedListItem(T item);
};

template <typename T>
class LinkedList
{
private:
	LinkedListItem<T>* start;
	//LinkedListItem<T>* end;
	//class LinkedListItem* end;

	//errors
	const int ERROR_INDEX_OUT_OF_RANGE = 1;
	const int ERROR_INVALID_SIZE = 2;
public:
	LinkedList();
	LinkedList(T* items, int count);
	LinkedList(const LinkedList <T>& list);

	~LinkedList();

	T GetFirst();
	T GetLast();
	T Get(int index);
	LinkedList<T>* GetSubList(int startIndex, int endIndex);
	int GetSize();
	void Append(T item);
	void Prepend(T item);
	void InsertAt(T item, int index);
	LinkedList<T>* Concat(LinkedList<T>* list);

	T& operator[](int index);
	void operator= (LinkedList<T> list);

};

template<typename T>
void LinkedList<T>::operator=(LinkedList<T> list) {
	LinkedListItem<T>* cur = this->start;
	if (cur == 0) {
		this->start = new LinkedListItem<T>;
		cur = this->start;
	}
	for (int i = 0; i < list.GetSize(); i++)
	{
		cur->item = list[i];
		if (i + 1 == list.GetSize())
		{
			cur->next = 0;
			break;
		}
		cur->next = new LinkedListItem<T>;
		cur = cur->next;
	}
}

template <typename T>
LinkedList<T>::LinkedList() {
	this->start = 0;
//	this->start->next = 0;
}

template <typename T>
LinkedList<T>::LinkedList(T* items, int count) {
//	if (count > 0)
//	{
		this->start = new LinkedListItem<T>;
		LinkedListItem<T>* cur = this->start;
		cur->item = items[0];
		for (int i = 1; i < count; i++)
		{
			cur->next = new LinkedListItem<T>;
			cur = cur->next;
			cur->item = items[i];
		}
		cur->next = 0;
//	}
//	this->start = 0;
}



template <typename T>
LinkedList<T>::LinkedList(const LinkedList <T>& list) {


	this->start = new LinkedListItem<T>;
	LinkedListItem<T>* cur1 = this->start;
	LinkedListItem<T>* cur2 = list.start;
	cur1->item = cur2->item;
	while (cur2->next != 0)
	{
		cur2 = cur2->next;
		cur1->next = new LinkedListItem<T>;
		cur1 = cur1->next;
		cur1->item = cur2->item;
	}
	cur1->next = 0;

}

template <typename T>
LinkedList<T>::~LinkedList() {

	if (this->start != NULL)
	{
		LinkedListItem<T>* cur = this->start;

		while (cur != 0)
		{
			LinkedListItem<T>* prev = cur;
			cur = cur->next;
			delete prev;
		}
		delete cur;
	}
}

template <typename T>
T LinkedList<T>::GetFirst() {
	if (this->start == 0)
	{
		throw ERROR_INDEX_OUT_OF_RANGE;
	}
	return this->start->item;
}

template <typename T>
T LinkedList<T>::GetLast() {
	if (this->start == 0)
	{
		throw ERROR_INDEX_OUT_OF_RANGE;
	}
	LinkedListItem<T>* cur = this->start;
	while (cur->next != 0)
	{
		cur = cur->next;
	}
	return cur->item;
}

template <typename T>
T LinkedList<T>::Get(int index) {
	LinkedListItem<T>* cur = this->start;
	for (int i = 0; i < index; i++)
		if (!cur)
			throw ERROR_INDEX_OUT_OF_RANGE;
		else
			cur = cur->next;
	if (!cur)
		throw ERROR_INDEX_OUT_OF_RANGE;
	return cur->item;
}
//
template <typename T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) {
	//	if (endIndex < startIndex)
	//		swap(startIndex, endIndex);
	if (startIndex < 0 || endIndex < 0 || startIndex >= (*this).GetSize() || endIndex >= (*this).GetSize())
	{
		throw ERROR_INDEX_OUT_OF_RANGE;
	}

	LinkedList<T>* res = new LinkedList<T>();

	for (int i = startIndex; i <= endIndex; i++)
	{
		res->Append((*this)[i]);
	}

	/*
	res->start->item = t1->item;
	res->start->next = new LinkedListItem<T>;
	t2 = res->start;
	for (int i = startIndex; i < endIndex; i++)
	{
		if (t1->next == 0) {
			throw ERROR_INDEX_OUT_OF_RANGE;
		}
		t2 = t1->next;
		t1 = t1->next;
	}
	delete t1;
	*/

	return res;
}
//
template <typename T>
int LinkedList<T>::GetSize() {
	if (this->start == 0) {
		return 0;
	}
	int res = 1;
	LinkedListItem<T>* cur = this->start;
	while (cur->next != 0)
	{
		res++;
		cur = cur->next;
	}
	return res;
}

template <typename T>
void LinkedList<T>::Append(T item) {
	
	if (this->start == NULL) {
		this->start = new LinkedListItem<T>;
		this->start->item = item;
		this->start->next = 0;
	}
	else
	{
		LinkedListItem<T>* cur = this->start;
		while (cur->next != 0)
			cur = cur->next;

		cur->next = new LinkedListItem<T>;
		cur->next->item = item;
		cur->next->next = 0;
	}
}

template <typename T>
void LinkedList<T>::Prepend(T item) {
	LinkedListItem<T>* cur = new LinkedListItem<T>;
	cur->item = item;
	cur->next = this->start;
	this->start = cur;

}

template <typename T>
void LinkedList<T>::InsertAt(T item, int index) {
	(*this)[index] = item;
}

template <typename T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) {
	LinkedList<T>* res = new LinkedList<T>();
	for (int i = 0; i < this->GetSize(); i++)
	{
		res->Append((*this)[i]);
	}
	for (int i = 0; i < list->GetSize(); i++)
	{
		res->Append((*list)[i]);
	}
	return res;
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
	if (index < 0)
		throw ERROR_INDEX_OUT_OF_RANGE;
	LinkedListItem<T>* cur = this->start;
	for (int i = 0; i < index; i++)
		if (cur == 0)
			throw ERROR_INDEX_OUT_OF_RANGE;
		else
			cur = cur->next;
	if (cur == 0)
		throw ERROR_INDEX_OUT_OF_RANGE;
	return cur->item;
}