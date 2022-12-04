#pragma once
#include <iostream>
#include "Sequence.h"
#include "B_Tree.h"
#include "Person.h"

using namespace std;

template <typename TKey, typename TElement>
class Pair
{
private:
	TKey key;
	TElement element;
public:
	Pair() {
		key = TKey();
		element = TElement();
	}

	Pair(TKey k, TElement el) {
		key = k;
		element = el;
	}
	~Pair();

	TKey GetKey() {
		return key;
	}
	TElement GetElement() {
		return element;
	}

	bool operator> (Pair<TKey, TElement> y);
	bool operator< (Pair<TKey, TElement> y);
	bool operator== (Pair<TKey, TElement> y);
	bool operator!= (Pair<TKey, TElement> y);
	Pair<TKey, TElement>& operator= (Pair<TKey, TElement> y);
};


template <typename TKey, typename TElement>
Pair<TKey, TElement>::~Pair()
{
}
template <typename TKey, typename TElement>
ostream& operator<<(ostream& os, Pair< TKey, TElement >& x) {
	os <<"(" << x.GetKey() << " ~ " << x.GetElement() << ")";
	return os;
}
template <typename TKey, typename TElement>
bool Pair<TKey, TElement>::operator> (Pair<TKey, TElement> y) {
	if (this->key > y.key )
	{
		return true;
	}
	else
	{
		return false;
	}
}
template <typename TKey, typename TElement>
bool Pair<TKey, TElement>::operator< (Pair<TKey, TElement> y) {
	if (this->key < y.key )
	{
		return true;
	}
	else
	{
		return false;
	}
}
template <typename TKey, typename TElement>
bool  Pair<TKey, TElement>::operator== (Pair<TKey, TElement> y) {
	if (this->key == y.key && this->element == y.element)
	{
		return true;
	}
	else
	{
		return false;
	}
}
template <typename TKey, typename TElement>
bool  Pair<TKey, TElement>::operator!= (Pair<TKey, TElement> y) {
	if (this->key != y.key || this->element != y.element)
	{
		return false;
	}
	else
	{
		return true;
	}
}
template <typename TKey, typename TElement>
Pair<TKey, TElement>& Pair<TKey, TElement>::operator= (Pair<TKey, TElement> y) {
	Pair<TKey, TElement>::key = y.key;
	Pair<TKey, TElement>::element = y.element;
	return *this;
}

template <typename TKey, typename TElement>
class IDictionary
{
private:
	int count;
	int capacity;

	BTree<Pair<TKey, TElement>> BTr;

public:
	
	IDictionary() {
		count = 0;
		capacity = 0;
		BTr = BTree<Pair<TKey, TElement>>();
	}
	IDictionary(int cap) {
		count = 0;
		capacity = cap;
		BTr = BTree<Pair<TKey, TElement>>();
	}
	
	IDictionary( int cap, int temp) {
		count = 0;
		capacity = cap;
		BTr = BTree<Pair<TKey, TElement>>(temp);
	}
	~IDictionary();

	int GetCount() {
		return count;
	}
	int GetCapacity() {
		return capacity;
	}
	BTree<Pair<TKey, TElement>> GetBTree() {
		return BTr;
	}
	TElement Get(TKey key);
	bool ContainsKey(TKey key);
	Pair<TKey, TElement> search(TKey key);
	void Add(TKey key, TElement element);
	void Remove(TKey key);


};



template <typename TKey, typename TElement>
IDictionary<TKey, TElement>::~IDictionary()
{
}

template <typename TKey, typename TElement>
bool IDictionary<TKey, TElement>::ContainsKey(TKey key) {

	if (BTr.GetRoot() == NULL)
	{
		return false;
	}
	BNode<Pair<TKey, TElement>>* cur = BTr.GetRoot();
	int i = 0;
	while (true)
	{


		while (i < cur->GetN() && key >(cur->GetKey(i)).GetKey()) {

			i++;
		}

		if ((cur->GetKey(i)).GetKey() == key) {

			return true;
		}

		if (cur->GetLeaf() == true) {

			return false;
		}
		cur = cur->GetChild(i);
	}
}

template <typename TKey, typename TElement>
Pair<TKey, TElement> IDictionary<TKey, TElement>::search(TKey key) {
	if (ContainsKey(key))
	{
		BNode<Pair<TKey, TElement>>* cur = BTr.GetRoot();
		int i = 0;
		while (true)
		{
			i = 0;
			while (i < cur->GetN() && key >(cur->GetKey(i)).GetKey())
				i++;
			if ((cur->GetKey(i)).GetKey() == key)
				return cur->GetKey(i);
			cur = cur->GetChild(i);
		}
	}

}

template <typename TKey, typename TElement>
void IDictionary<TKey, TElement>::Add(TKey key, TElement element) {
//	if (!ContainsKey(key) && capacity > 0)
//	{
		Pair<TKey, TElement> pair(key, element);
		BTr.insert(pair);
		count++;
		capacity--;
//	}
	
}

template <typename TKey, typename TElement>
void IDictionary<TKey, TElement>::Remove(TKey key) {
	
	if (ContainsKey(key))
	{
		BTr.remove(search(key));
		count--;
		capacity++;
	}
}

template <typename TKey, typename TElement>
TElement IDictionary<TKey, TElement>::Get(TKey key) {

	if (ContainsKey(key))
	{
		return (search(key)).GetElement();
	}
}