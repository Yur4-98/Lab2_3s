#pragma once
#include "IDictionary.h"
#include <iostream>
#include "Person.h"
#include "Tree.h"

template <typename T>
struct Index
{
	
};




template <typename TKey>
void IndexOfDataFIO(ArraySequence<Person> Obj, IDictionary<TKey, Person>* res) {
	
	ArraySequence<Pair<TKey, Person>> d = res->GetBTree().traverse();
	for (int i = 0; i < d.GetSize(); i++)
	{
		res->Remove(d[i].GetKey());
	}
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		TKey str = Obj[i].GetFIO();
		if (res->ContainsKey(Obj[i].GetFIO()))
		{
			while (res->ContainsKey(str))
			{
				str += "1";
			}
		}
		res->Add(Obj[i].GetFIO(), Obj[i]);
	}
	
}
template <typename TKey>
void IndexOfDataFN(ArraySequence<Person> Obj, IDictionary<TKey, Person>* res) {
	
	ArraySequence<Pair<TKey, Person>> d = res->GetBTree().traverse();
	for (int i = 0; i < d.GetSize(); i++)
	{
		res->Remove(d[i].GetKey());
	}
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		TKey str = Obj[i].GetFirstName();
		if (res->ContainsKey(Obj[i].GetFirstName()))
		{
			while (res->ContainsKey(str))
			{
				str += "1";
			}
		}
		res->Add(Obj[i].GetFirstName(), Obj[i]);
	}
}
template <typename TKey>
void IndexOfDataMN(ArraySequence<Person> Obj, IDictionary<TKey, Person>* res) {
	
	ArraySequence<Pair<TKey, Person>> d = res->GetBTree().traverse();
	for (int i = 0; i < d.GetSize(); i++)
	{
		res->Remove(d[i].GetKey());
	}
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		TKey str = Obj[i].GetMiddleName();
		if (res->ContainsKey(Obj[i].GetMiddleName()))
		{
			while (res->ContainsKey(str))
			{
				str += "1";
			}
		}
		res->Add(Obj[i].GetMiddleName(), Obj[i]);
	}
}
template <typename TKey>
void IndexOfDataLN(ArraySequence<Person> Obj, IDictionary<TKey, Person>* res) {
	
	ArraySequence<Pair<TKey, Person>> d = res->GetBTree().traverse();
	for (int i = 0; i < d.GetSize(); i++)
	{
		res->Remove(d[i].GetKey());
	}
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		TKey str = Obj[i].GetLastName();
		if (res->ContainsKey(Obj[i].GetLastName()))
		{
			while (res->ContainsKey(str))
			{
				str += "1";
			}
		}
		res->Add(Obj[i].GetLastName(), Obj[i]);
	}
}
template <typename TKey>
void IndexOfDataFullN(ArraySequence<Person> Obj, IDictionary<TKey, Person>* res) {
	
	ArraySequence<Pair<TKey, Person>> d = res->GetBTree().traverse();
	for (int i = 0; i < d.GetSize(); i++)
	{
		res->Remove(d[i].GetKey());
	}
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		TKey str = Obj[i].GetFullName();
		if (res->ContainsKey(Obj[i].GetFullName()))
		{
			while (res->ContainsKey(str))
			{
				str += "1";
			}
		}
		res->Add(Obj[i].GetFullName(), Obj[i]);
	}
}
template <typename TKey>
void IndexOfDataBD(ArraySequence<Person> Obj, IDictionary<TKey, Person>* res) {
	
	ArraySequence<Pair<TKey, Person>> d = res->GetBTree().traverse();
	for (int i = 0; i < d.GetSize(); i++)
	{
		res->Remove(d[i].GetKey());
	}
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		TKey str = Obj[i].GetBirthYear();
		if (res->ContainsKey(Obj[i].GetBirthYear()))
		{
			while (res->ContainsKey(str))
			{
				str += 1;
			}
		}
		res->Add(Obj[i].GetBirthYear(), Obj[i]);
	}
}
template <typename TKey>
void IndexOfDataAge(ArraySequence<Person> Obj, IDictionary<TKey, Person>* res) {
	
	ArraySequence<Pair<TKey, Person>> d = res->GetBTree().traverse();
	for (int i = 0; i < d.GetSize(); i++)
	{
		res->Remove(d[i].GetKey());
	}
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		TKey str = Obj[i].GetAge(2022);
		if (res->ContainsKey(Obj[i].GetAge(2022)))
		{
			while (res->ContainsKey(str))
			{
				str += 1;
			}
		}
		res->Add(Obj[i].GetAge(2022), Obj[i]);
	}
}

template <typename TKey, typename TElement>
IDictionary<TKey, Person> IndexOfData(ArraySequence<Person> Obj, int NumberOfAtribute) {
	IDictionary<int, Person> res(Obj.GetSize());
	IDictionary<string, Person> res1(Obj.GetSize());
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		switch (NumberOfAtribute)
		{
		case(1):
			
			IndexOfDataFIO<string>(Obj ,&res1);
			return res1;
			break;
		case(2):
			IndexOfDataFN<string>(Obj ,&res1);
			return res1;
			break;
		case(3):
			IndexOfDataMN<string>(Obj ,&res1);
			return res1;
			break;
		case(4):
			IndexOfDataLN<string>(Obj ,&res1);
			return res1;
			break;
		case(5):
			IndexOfDataFullN<string>(Obj ,&res1);
			return res1;
			break;
		case(6):
			IndexOfDataBD<int>(Obj ,&res);
			return res;
			break;
		case(7):
			IndexOfDataAge<int>(Obj ,&res);
			return res;
			break;
		default:
			//
			break;
		}
	}

}


/*
template <typename TKey, typename TElement>
IDictionary<TKey, Person> IndexOfData(ArraySequence<Person> Obj,
	ArraySequence<int> NumbersOfAtribute) {
	IDictionary<TKey, Person> res(Obj.GetSize());
	for (int i = 0; i < Obj.GetSize(); i++)
	{
		for (int j = 0; j < NumbersOfAtribute.GetSize(); j++)
		{

		}
	}

}*/
/////////////////////////////////////////////////////////////
template <typename TKey, typename TElement>
class Cash
{
private:
	IDictionary<TKey, TElement> cash;
	BTree<Pair<int, TKey>> HowMuch;
	Tree<Pair<int, TKey>> HowMuch_1;
	int time;
public:
	Cash() {
		cash = IDictionary<TKey, TElement>(10);
		HowMuch = BTree<Pair<int, TKey>>();
		//HowMuch_1 = Tree<Pair<int, TKey>>();
		time = 0;
	}
	Cash(int cap) {
		cash = IDictionary<TKey, TElement>(cap);
		HowMuch = BTree<Pair<int, TKey>>();
		//HowMuch_1 = Tree<Pair<int, TKey>>();
		time = 0;
	}
	~Cash() {

	}


	IDictionary<TKey, TElement> GetCash() {
		return cash;
	}

	int GetCount() {
		return cash.GetCount();
	}
	int GetCapacity() {
		return cash.GetCapacity();
	}
	
	TElement Get(TKey key);
	bool ContainsKey(TKey key);
	Pair<TKey, TElement> search(TKey key);
	void Add(TKey key, TElement element);
	//void Remove(TKey key);
};

template <typename TKey, typename TElement>
bool Cash<TKey, TElement>::ContainsKey(TKey key) {
	return cash.ContainsKey(key);
}
template <typename TKey, typename TElement>
Pair<TKey, TElement> Cash<TKey, TElement>::search(TKey key) {
	return cash.search(key);
}
template <typename TKey, typename TElement>
void Cash<TKey, TElement>::Add(TKey key, TElement element) {
	if (GetCapacity()>0)
	{
		if (ContainsKey(key))
		{
			ArraySequence<Pair<int, TKey>> seq = HowMuch.traverse();
			//DynamicArray<Pair<int, TKey>> seq = HowMuch_1.InOrder();

			int i = 0;
			while (key != seq[i].GetElement()) {
				i++;
			}
			Pair<int, TKey> pair = seq[i];
			HowMuch.remove(pair);
			//HowMuch_1.Remove(pair);
			Pair<int, TKey> pair1(time, pair.GetElement());
			HowMuch.insert(pair1);
			//HowMuch_1.Insert(pair1);
			time++;
		}
		else
		{
			Pair<int, TKey> pair(time,key);
			time++;
			cash.Add(key, element);
			HowMuch.insert(pair);
			//HowMuch_1.Insert(pair1);

		}
	}
	else
	{
		if (ContainsKey(key))
		{
			ArraySequence<Pair<int, TKey>> seq = HowMuch.traverse();
			//DynamicArray<Pair<int, TKey>> seq = HowMuch_1.InOrder();
			int i = 0;
			while (key != seq[i].GetElement()) {
				i++;
			}
			Pair<int, TKey> pair = seq[i];
			HowMuch.remove(pair);
			//HowMuch_1.Remove(pair);
			Pair<int, TKey> pair1(time, pair.GetElement());
			HowMuch.insert(pair1);
			//HowMuch_1.Insert(pair1);
			time++;
		}
		else
		{
			Pair<int, TKey> pair(time, key);
			time++;
			ArraySequence<Pair<int, TKey>> seq = HowMuch.traverse();
			//DynamicArray<Pair<int, TKey>> seq = HowMuch_1.InOrder();
			Pair<int, TKey> pair1 = seq[0];
			cash.Remove(pair1.GetElement());
			cash.Add(key, element);
			HowMuch.remove(pair1);
			//HowMuch_1.Remove(pair);
			HowMuch.insert(pair);
			//HowMuch_1.Insert(pair1);

		}
	}
}
template <typename TKey, typename TElement>
TElement Cash<TKey, TElement>::Get(TKey key) {
	if (ContainsKey(key))
	{
		Pair<int, TKey> pair1;
		Pair<int, TKey> pair(time, key);
		time++;
		ArraySequence<Pair<int, TKey>> seq = HowMuch.traverse();
		//DynamicArray<Pair<int, TKey>> seq = HowMuch_1.InOrder();
		for (int i = 0; i < seq.GetSize(); i++)
		{
			if (seq[i].GetElement() == key)
			{
				pair1 = seq[0];
			}
		}		
		HowMuch.remove(pair1);
		//HowMuch_1.Remove(pair);
		HowMuch.insert(pair);
		//HowMuch_1.Insert(pair1);
		return (search(key)).GetElement();
	}
	else
	{

	}
}
