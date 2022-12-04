#pragma once

#include <iostream>
#include <cmath>
#include "Complex.h"
#include <string>
#include "DynamicArray.h"

using namespace std;

template< typename T> class N_Tree;

template <typename T>
class N_TreeItem
{
	friend class N_Tree <T>;

private:
	T item;
	int N;
	DynamicArray<N_TreeItem<T>*> childs;

	const int ERROR_INDEX_OUT_OF_RANGE = 1;
	const int ERROR_INVALID_SIZE = 2;
public:
	N_TreeItem(T item, int N);
	~N_TreeItem();

	T& operator[](int index);

	T GetItem();
	N_TreeItem<T>* GetChild(int index);

	void printall();
//	void add(T data, int child, int N);
};


template <typename T>
void N_TreeItem<T>::printall() {

	if (this != NULL) {//клп
		cout << this->item;//проверить перегрузку вывода
		(*(this->childs.GetFirst())).printall();
		(*(this->childs.GetLast())).printall();
	}

	/*
	if (this != NULL) {//кпл
		cout << this->item;//проверить перегрузку вывода
		(*(this->childs.GetLast())).printall();
		(*(this->childs.GetFirst())).printall();
	}

	if (this != NULL) {//плк
		(*(this->childs.GetLast())).printall();
		(*(this->childs.GetFirst())).printall();
		cout << this->item;//проверить перегрузку вывода
	}

	if (this != NULL) {//лпк
		(*(this->childs.GetLast())).printall();
		(*(this->childs.GetFirst())).printall();
		cout << this->item;//проверить перегрузку вывода
	}

	*/
}

template <typename T>
T& N_TreeItem<T>::operator[](int index) {
	return this->GetChild(index);
}

template<typename T>
N_TreeItem<T>::N_TreeItem(T Item, int N){
	this->item = Item;
	this->N = N;
	this->childs = DynamicArray<N_TreeItem<T>*>(N,0);
}

template<typename T>
N_TreeItem<T>::~N_TreeItem(){

}

template<typename T>
T N_TreeItem<T>::GetItem() {
	return this->item;
}

template<typename T>
N_TreeItem<T>* N_TreeItem<T>::GetChild(int index) {
	if (index < 0 || index > this->N) {
		throw ERROR_INDEX_OUT_OF_RANGE;
	}
	return this->childs[index];
}

template<typename T>
class N_Tree
{
private:
	N_TreeItem<T>* start;
	int N;
	void insert_helper(N_TreeItem< T >**, const T&, int *way, int depth);

	const int ERROR_INVALID_WAY = 3;
public:
	N_Tree();
	N_Tree(int N);
	~N_Tree();

	void set(T &);
	void remove(T &);
	
	void insert(const T&, int* way, int depth);
	void print();
///	void add(T data, int* way, int depth);
};

template< typename T>
void N_Tree<T>::insert(const T& data, int *way, int depth)
{
	insert_helper(&start, data, way, depth);
}

template< typename T >
void N_Tree<T>::insert_helper(N_TreeItem< T >** node, const T& data, int *way, int depth)
{
	if (*node == 0)
		*node = new N_TreeItem<T>(data,this->N);
	else
	{
		if (depth == 0)
		{
			throw ERROR_INVALID_WAY;
		}
		insert_helper(&((*node)->childs[*way]), data, way + sizeof(int),depth - 1);

	}
}
/*
//доделать
template <typename T>
void N_Tree<T>::add(T data, int* way, int depth) {
	if (this->start == 0) { // Если дерева нет, то формируем корень
		this->start = new N_TreeItem<T>(data, this->N);
	}
	else {
		N_TreeItem<T>* newitem = new N_TreeItem<T>(data, this->N);
		N_TreeItem<T>* cur = this->start;
		for (int i = 0; i < depth; i++)
		{
			cur = cur->GetChild(way[i]);//!!!!!!!!!!!!!
			if (cur == 0 && i < depth)
			{
				throw ERROR_INVALID_WAY;
			}
		}
		cur = newitem;
	}


}
*/
template <typename T>
N_Tree<T>::N_Tree() {
	this->start = 0;
	this->N = 2;
}

template <typename T>
N_Tree<T>::N_Tree(int N){
	this->N = N;
	this->start = 0;
}

template <typename T>
void N_Tree<T>::set(T& data) {

}

template <typename T>
void N_Tree<T>::remove(T& data) {}

template <typename T>
void N_Tree<T>::print() {
	this->start->printall();
}

template <typename T>
N_Tree<T>::~N_Tree() {}
