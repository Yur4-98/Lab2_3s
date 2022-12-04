#pragma once
#include <iostream>
#include "Sequence.h"

using namespace std;

template < typename T> class BTree;

template < typename T>
class BNode {

	friend class BTree<T>;
private:
	ArraySequence<T> keys;
	int t;
	ArraySequence<BNode*> Children;
	BNode* parent;
	int n;
	bool leaf;

public:
	int GetN() {
		return n;
	}
	T GetKey(int i) {
		return keys[i];
	}
	BNode* GetChild(int i) {
		return Children[i];
	}
	bool GetLeaf() {
		return leaf;
	}
	int GetT() {
		return t;
	}
	BNode* GetParent() {
		return parent;
	}

	BNode(int temp, bool bool_leaf);
	BNode(int temp, bool bool_leaf, BNode *parent);

	void insertNonFull(T k);
	
	void splitChild(int i, BNode* y);
	void traverse(ArraySequence<T> *traver);

	BNode* search(T k);
};

template < typename T>
class BTree {
private:

	BNode<T>* root;
	int t;

	
	void removeFromLeaf(T key, BNode<T> *node);
	void removeFromNode(T key, BNode<T>* node);
	void connect(BNode<T>* node);
public:
	
	BNode<T>* GetRoot() {
		return root;
	}
	int GetT() {
		return t;
	}

	BTree(int temp) {
		root = NULL;
		t = temp;
	}
	BTree() {
		root = NULL;
		t = 2;
	}

	ArraySequence<T> traverse() {
		ArraySequence<T> traver;
		if (root != NULL) {	
			root->traverse(&traver);
		}
		return traver;
	}

	BNode<T>* search(T k) {
		return (root == NULL) ? NULL : root->search(k);
	}

	void insert(T k);
	
	void remove(T key);
	
};

template < typename T>
BNode<T>::BNode(int t1, bool leaf1) {
	t = t1;
	leaf = leaf1;
	keys = ArraySequence<T>(2 * t - 1);
	Children = ArraySequence<BNode*>(2 * t);
	parent = NULL;
	n = 0;
}

template < typename T>
BNode<T>::BNode(int t1, bool leaf1, BNode<T> *p) {
	t = t1;
	leaf = leaf1;
	keys = ArraySequence<T>(2 * t - 1);
	Children = ArraySequence<BNode*>(2 * t);
	parent = p;
	n = 0;
}

template < typename T>
void BNode<T>::traverse(ArraySequence<T> *traver) {
	int i;
	for (i = 0; i < n; i++) {
		if (leaf == false)
			Children[i]->traverse(traver);
		traver->Append(keys[i]);
		//cout << " " << keys[i];
	}

	if (leaf == false)
		Children[i]->traverse(traver);
}

template < typename T>
BNode<T>* BNode<T>::search(T k) {
	int i = 0;
	while (i < n && k > keys[i])
		i++;

	if (keys[i] == k)
		return this;

	if (leaf == true)
		return NULL;

	return Children[i]->search(k);
}

template < typename T>
void BTree<T>::insert(T k) {
	if (root == NULL) {
		root = new BNode<T>(t, true);
		root->keys[0] = k;
		root->n = 1;
	}
	else {
		if (root->n == 2 * t - 1) {
			BNode<T>* s = new BNode<T>(t, false);

			root->parent = s;//

			s->Children[0] = root;
			s->splitChild(0, root);

			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->Children[i]->insertNonFull(k);

			root = s;
		}
		else
			root->insertNonFull(k);
	}
}

template < typename T>
void BNode<T>::insertNonFull(T k) {
	int i = n - 1;

	if (leaf == true) {
		while (i >= 0 && keys[i] > k) {
			keys[i + 1] = keys[i];
			i--;
		}

		keys[i + 1] = k;
		n = n + 1;
	}
	else {
		while (i >= 0 && keys[i] > k)
			i--;

		if (Children[i + 1]->n == 2 * t - 1) {
			splitChild(i + 1, Children[i + 1]);

			if (keys[i + 1] < k)
				i++;
		}
		Children[i + 1]->insertNonFull(k);
	}
}

template < typename T>
void BNode<T>::splitChild(int i, BNode<T>* y) {
	BNode* z = new BNode(y->t, y->leaf, y->parent);//
	z->n = t - 1;

	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];

	if (y->leaf == false) {
		for (int j = 0; j < t; j++)
			z->Children[j] = y->Children[j + t];
	}

	y->n = t - 1;
	for (int j = n; j >= i + 1; j--)
		Children[j + 1] = Children[j];

	Children[i + 1] = z;

	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	keys[i] = y->keys[t - 1];
	n = n + 1;
}

////////////////////////////////////////

template < typename T>
void BTree<T>::removeFromLeaf(T key, BNode<T> *node) {
	
	

	for (int i = 0; i < node->n; i++) {
		if (node->keys[i] == key) {
			for (int j = i; j < node->n; j++) {
				node->keys[j] = node->keys[j + 1];
				node->Children[j] = node->Children[j + 1];
			}
			node->keys[node->n - 1] = T();
			node->Children[node->n - 1] = node->Children[node->n];
			node->Children[node->n] = NULL;
			break;
		}
	}
	(node->n)--;

	if (node == root && node->leaf == true)
	{
		return;
	}
	if (node->n >= t - 1)
	{
		return;
	}
	int m = 0;
	for (int i = 0; i < node->parent->n+1; i++)
	{
		if (node->parent->Children[i] == node)
		{
			m = i;
			break;
		}
	}
	if ((m > 0) ? (node->parent->Children[m-1]->n >= t) : false)
	{
		node->insertNonFull(node->parent->keys[m - 1]);
		node->parent->keys[m - 1] = (node->parent->Children[m - 1])->keys[(node->parent->Children[m - 1])->n - 1];
		removeFromLeaf((node->parent->Children[m - 1])->keys[(node->parent->Children[m - 1])->n - 1], node->parent->Children[m - 1]);
		return;
	}
	if ((m < node->parent->n) ? (node->parent->Children[m + 1]->n >= t) : false)
	{
		node->insertNonFull(node->parent->keys[m]);
		node->parent->keys[m] = (node->parent->Children[m + 1])->keys[0];
		removeFromLeaf((node->parent->Children[m + 1])->keys[0], node->parent->Children[m + 1]);
		return;
	}
	connect(node);
	/*
	if (m > 0)
	{
		for (int i = 0; i < node->n; i++)
		{
			(node->parent->Children[m - 1])->insertNonFull(node->keys[i]);
			(node->parent->Children[m - 1])->n++;
		}
		(node->parent->Children[m - 1])->insertNonFull(node->parent->keys[m - 1]);
		(node->parent->Children[m - 1])->n++;
		//removeFromNode(node->parent->keys[m - 1], node->parent);
		for (int i = m; i < node->parent->n - 1; i++)
		{
			node->parent->Children[i] = node->parent->Children[i + 1];
			node->parent->keys[i - 1] = node->parent->keys[i];
		}
		node->parent->keys[node->parent->n - 1] = T(0);
		node->parent->Children[node->parent->n] = NULL;
		node->parent->n--;

		if (node->parent->n == t-2)
		{

		}

		return;
	}
	if (m < node->parent->n)
	{
		for (int i = 0; i < (node->parent->Children[m + 1])->n; i++)
		{
			(node->insertNonFull((node->parent->Children[m + 1])->keys[i]);
			(node->n++;
		}
		node->insertNonFull(node->parent->keys[m]);
		node->n++;
		//removeFromNode(node->parent->keys[m], node->parent);
		for (int i = m; i < node->parent->n - 1; i++)
		{
			node->parent->Children[i + 1] = node->parent->Children[i + 2];
			node->parent->keys[i] = node->parent->keys[i + 1];
		}
		node->parent->keys[node->parent->n - 1] = T(0);
		node->parent->Children[node->parent->n] = NULL;
		node->parent->n--;

		if (node->parent->n == t - 2)
		{

		}
		
		return;
	}*/
}

template < typename T>
void BTree<T>::removeFromNode(T key, BNode<T>* node) {
	T K;

	int m = 0;
	for (int i = 0; i < node->n; i++)
	{
		if (node->keys[i] == key)
		{
			m = i;
			break;
		}
	}

	BNode<T> *n = node->Children[m];
	while (!(n->leaf))
	{
		n = n->Children[n->n];
	}
	K = n->keys[n->n - 1];
	node->keys[m] = K;
	removeFromLeaf(n->keys[n->n - 1], n);
		
}

template < typename T>
void BTree<T>::remove(T key) {


	if (!search(key))
	{
		return;
	}
	if (root->leaf == true)
	{
		removeFromLeaf(key, root);
		return;
	}
	BNode<T>* node = search(key);
	if (node->leaf)
	{
		removeFromLeaf(key, node);
	}
	else
	{
		removeFromNode(key, node);
	}
}
template < typename T>
void BTree<T>::connect(BNode<T>* node) {
	int m = 0;
	for (int i = 0; i < node->parent->n + 1; i++)
	{
		if (node->parent->Children[i] == node)
		{
			m = i;
			break;
		}
	}

	if (m > 0)//left connect
	{
		
		for (int i = node->n; i > 0; i--)
		{
			node->keys[i] = node->keys[i - 1];
			node->Children[i + 1] = node->Children[i];
		}
		node->Children[1] = node->Children[0];
		node->keys[0] = node->parent->keys[m - 1];
		node->Children[0] = (node->parent->Children[m - 1])->Children[(node->parent->Children[m - 1])->n];
		(node->n)++;

		for (int j = 0; j < (node->parent->Children[m - 1])->n; j++)
		{
			for (int i = node->n; i > 0; i--)
			{
				node->keys[i] = node->keys[i - 1];
				node->Children[i + 1] = node->Children[i];
			}
			node->Children[1] = node->Children[0];

			node->keys[0] = (node->parent->Children[m - 1])->keys[(node->parent->Children[m - 1])->n - 1];
			node->Children[0] = (node->parent->Children[m - 1])->Children[(node->parent->Children[m - 1])->n - 1];
			((node->parent->Children[m - 1])->n)--;
			(node->n)++;

		}
		

		for (int i = m - 1; i < node->parent->n - 1; i++)
		{
			node->parent->Children[i] = node->parent->Children[i + 1];
			node->parent->keys[i - 1] = node->parent->keys[i];
		}
		node->parent->keys[node->parent->n - 1] = T();
		node->parent->Children[node->parent->n] = NULL;
		node->parent->n--;
		//
		if (node->parent == root && node->parent->n > 0)
		{
			return;
			cout << '*' << endl;
		}
		if (node->parent == root && node->parent->n == 0) 
		{
			root = node->parent->Children[0];
			root->parent = NULL;
			return;
			
		}

		if (node->parent->n == t - 2)
		{
			connect(node->parent);
		}
		//
		return;
	}
	if (m < node->parent->n)//right connect
	{
		
		
		node->keys[node->n] = node->parent->keys[m];
		node->Children[node->n + 1] = (node->parent->Children[m + 1])->Children[0];
		(node->n)++;

		for (int j = 0; j < (node->parent->Children[m + 1])->n; j++)
		{

			node->keys[node->n] = (node->parent->Children[m + 1])->keys[j];
			node->Children[node->n + 1] = (node->parent->Children[m + 1])->Children[j + 1];
			(node->n)++;

		}



		for (int i = m; i < node->parent->n - 1; i++)
		{
			node->parent->keys[i] = node->parent->keys[i + 1];
			node->parent->Children[i + 1] = node->parent->Children[i + 2];
			
		}
		node->parent->keys[node->parent->n - 1] = T();
		node->parent->Children[node->parent->n] = NULL;
		(node->parent->n)--;
	
		//
		if (node->parent == root && node->parent->n > 0)
		{
			
			return;
			
		}
		if (node->parent == root && node->parent->n == 0)
		{

			root = node->parent->Children[0];
			root->parent = NULL;
			return;
			
		}

		if (node->parent->n == t - 2)
		{
			connect(node->parent);
		}
		return;
	}
}
