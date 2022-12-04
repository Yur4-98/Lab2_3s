#pragma once
#include <iostream>
#include "DynamicArray.h"
using namespace std;

template <typename T>
T mult(T t) {
    return t * 2;
}
template <typename T>
bool ch(T t) {
    return t > 5;
}

template< typename T> class Tree;

template< typename T>
class Node
{
    friend class Tree<T>;

public:
    Node();
    Node(const T&);

    T GetItem() const;

private:
    T item;
    Node<T>* left;
    Node<T>* right;

    int height;
};

template< typename T >
Node<T>::Node() :
    left(0),
    right(0),
    height(0)
{
}

template< typename T >
Node<T>::Node(const T& data) :
    item(data),
    left(0),
    right(0),
    height(1)
{
}

template< typename T >
T Node<T>::GetItem() const
{
    return item;
}

template< typename T>
class Tree
{
    template< typename Type>
    friend Type max(const Type&, const Type&);

public:
    Tree();
    Tree(DynamicArray<T>);
    ~Tree();

    bool Find(T);
    bool FindTree(Tree<T>);

    void Insert(const T&);
    void Remove(const T&);

    DynamicArray<T> PreOrder() const;//клп
    DynamicArray<T> InOrder() const;//лкп
    DynamicArray<T> PostOrder() const;//лпк
    DynamicArray<T> Order4() const;//кпл
    DynamicArray<T> Order5() const;//плк
    DynamicArray<T> Order6() const;//пкл


    int Depth() const;
    void Print() const;

    Tree<T>* Map(T(*func)(T));
    Tree<T>* Where(bool (*func)(T));
    Tree<T>* merge(Tree<T> *);

    Tree<T>* NewTree(const T&);
private:
    Node<T>* root;

    void InsertHelper(Node<T>**, const T&);
    void RemoveHelper(Node<T>**, const T&);

    void PreOrderNode(Node<T>*, DynamicArray<T>*) const;
    void InOrderNode(Node<T>*, DynamicArray<T>*) const;
    void PostOrderNode(Node<T>*, DynamicArray<T>*) const;
    void Order4Node(Node<T>*, DynamicArray<T>*) const;
    void Order5Node(Node<T>*, DynamicArray<T>*) const;
    void Order6Node(Node<T>*, DynamicArray<T>*) const;

    void DeleteNode(Node<T>*);

    int DepthNode(Node<T>*) const;

    void PrintNode(Node<T>*, int) const;


    int height(Node<T>*);
    int bfactor(Node<T>*);
    void fixheight(Node<T>*);

    Node<T>* rotateright(Node<T>*);
    Node<T>* rotateleft(Node<T>*);
    Node<T>* balance(Node<T>*);

    Node<T>* findmin(Node<T>*);
    Node<T>* removemin(Node<T>*);
};

template <typename T>
Node<T>* Tree<T>::findmin(Node<T>* p)
{
    return p->left ? findmin(p->left) : p;
}

template <typename T>
Node<T>* Tree<T>::removemin(Node<T>* p) {
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

template <typename T>
Node<T>* Tree<T>::rotateright(Node<T>* node){
    Node<T>* q = (node)->left;
    (node)->left = q->right;
    q->right = (node);
    fixheight(node);
    fixheight(q);
    return q;
    
}

template <typename T>
Node<T>* Tree<T>::rotateleft(Node<T>* node){
    Node<T>* p = (node)->right;
    (node)->right = p->left;
    p->left = node;
    fixheight(node);
    fixheight(p);
    return p;
}

template <typename T>
Node<T>* Tree<T>::balance(Node<T>* p)
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

template <typename T>
void Tree<T>::fixheight(Node<T>* p) {
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

template <typename T>
int Tree<T>::height(Node<T>* p) {
    return p ? p->height : 0;
}

template <typename T>
int Tree<T>::bfactor(Node<T>* p) {
    return height(p->right) - height(p->left);
}

template< typename T>
Tree<T>::Tree():root(0)
{
}

template< typename T>
Tree<T>::Tree(DynamicArray<T> arr):root(0) {
    for (int i = 0; i < arr.GetSize(); i++)
    {
        this->Insert(arr[i]);
    }
}

template< typename T>
Tree<T>::~Tree()
{
    DeleteNode(root);
}

template< typename T>
void Tree<T>::DeleteNode(Node<T>* node)
{
    if (node != 0)
    {
        DeleteNode(node->left);
        DeleteNode(node->right);

        delete node;
    }
}

template<typename T>
bool Tree<T>::FindTree(Tree<T> tr){
    DynamicArray<T> a1, a2;


    Node<T>* curr = root;
    while (curr && curr->item != tr.root->item)
    {
        if (curr->item > tr.root->item)
            curr = curr->left;
        else
            curr = curr->right;
    }

    Tree<T> tr1;
    tr1.root = curr;
    a1 = tr1.PreOrder();
    a2 = tr.PreOrder();

    return a1 == a2;
}

template<typename T>
bool Tree<T>::Find(T data) {

    Node<T>* curr = root;
    while (curr && curr->item != data)
    {
        if (curr->item > data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr != NULL;

}

template< typename T>
void Tree<T>::Insert(const T& data)
{
    InsertHelper(&root, data);
}

template< typename T>
void Tree<T>::InsertHelper(Node<T>** node, const T& data)
{
    if (*node == 0)
        *node = new Node<T>(data);
    else
    {
        if ((*node)->item > data)
            InsertHelper(&((*node)->left), data);
        else
        {
            if ((*node)->item < data)
                InsertHelper(&((*node)->right), data);
        }
    }
    *node = balance(*node);
}

template< typename T >
void Tree<T>::Remove(const T& data)
{
    RemoveHelper(&root, data);
}

template< typename T >
void Tree<T>::RemoveHelper(Node<T>** node, const T& data) {
    
    if (!(*node)) { return; }
    if (data < (*node)->item)
        RemoveHelper(&((*node)->left), data);
    else if (data > (*node)->item)
        RemoveHelper(&((*node)->right), data);
    else 
    {
        Node<T>* q = (*node)->left;
        Node<T>* r = (*node)->right;
        delete *node;
        if (!r) 
        {
            *node = q;
            return ;
        }
        Node<T>* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        *node = balance(min);
    }
    *node = balance(*node);
}

template< typename T >
DynamicArray<T> Tree<T>::PreOrder() const
{
    DynamicArray<T> arr;
    PreOrderNode(root, &arr);
    return arr;

}

template< typename T >
void Tree<T>::PreOrderNode(Node<T>* node, DynamicArray<T>* arr) const
{
    if (node != 0)
    {
        arr->Append(node->item);
 //       cout << node->item << "  ";

        PreOrderNode(node->left, arr);
        PreOrderNode(node->right, arr);
    }
}

template< typename T >
DynamicArray<T> Tree<T>::InOrder() const
{
    DynamicArray<T> arr;
    InOrderNode(root, &arr);
    return arr;
}

template< typename T >
void Tree< T >::InOrderNode(Node<T>* node, DynamicArray<T>* arr) const
{
    if (node != 0)
    {
        InOrderNode(node->left, arr);
 
        arr->Append(node->item);
 //     cout << node->item << "  ";

        InOrderNode(node->right, arr);
    }
}

template< typename T >
DynamicArray<T> Tree<T>::PostOrder() const
{
    DynamicArray<T> arr;
    PostOrderNode(root, &arr);
    return arr;
}

template< typename T >
void Tree<T>::PostOrderNode(Node<T>* node, DynamicArray<T>* arr) const
{
    if (node != 0)
    {
        PostOrderNode(node->left,arr);
        PostOrderNode(node->right,arr);

        arr->Append(node->item);
//      cout << node->item << "  ";
    }
}

template< typename T >
DynamicArray<T> Tree<T>::Order4() const
{
    DynamicArray<T> arr;
    Order4Node(root, &arr);
    return arr;
}

template< typename T >
void Tree<T>::Order4Node(Node<T>* node, DynamicArray<T>* arr) const
{
    if (node != 0)
    {
        arr->Append(node->item);
        //      cout << node->item << "  ";
        PostOrderNode(node->right, arr);
        PostOrderNode(node->left, arr);
    }
}

template< typename T >
DynamicArray<T> Tree<T>::Order5() const
{
    DynamicArray<T> arr;
    Order5Node(root, &arr);
    return arr;
}

template< typename T >
void Tree<T>::Order5Node(Node<T>* node, DynamicArray<T>* arr) const
{
    if (node != 0)
    {
        PostOrderNode(node->right, arr);
        PostOrderNode(node->left, arr);
        
        arr->Append(node->item);
        //      cout << node->item << "  ";
    }
}

template< typename T >
DynamicArray<T> Tree<T>::Order6() const
{
    DynamicArray<T> arr;
    Order6Node(root, &arr);
    return arr;
}

template< typename T >
void Tree<T>::Order6Node(Node<T>* node, DynamicArray<T>* arr) const
{
    if (node != 0)
    {
        PostOrderNode(node->right, arr);
        arr->Append(node->item);
        //      cout << node->item << "  ";
        PostOrderNode(node->left, arr);
    }
}

template< typename T >
int Tree<T>::Depth() const
{
    return DepthNode(root);
}

template< typename T >
int Tree<T>::DepthNode(Node<T>* node) const
{
    if (node->left == 0 && node->right == 0)
        return 1;
    else
    {
        if (node->left == 0)
            return 1 + DepthNode(node->right);
        else
        {
            if (node->right == 0)
                return 1 + DepthNode(node->left);
            else
                return 1 + (DepthNode(node->left) > DepthNode(node->right) ? DepthNode(node->left) : DepthNode(node->right));
                
        }
    }
}

template< typename T >
void Tree<T>::Print() const
{
    PrintNode(root, 0);
}

template< typename T >
void Tree<T>::PrintNode(Node<T>* node, int spaces) const
{
    while (node != 0)
    {
        PrintNode(node->right, spaces + 5);

        for (int i = 1; i < spaces; ++i)
            cout << ' ';

        cout << node->item << endl;

        node = node->left;
        spaces += 5;
    }
}

template< typename T >
Tree<T>* Tree<T>::Map(T (*func)(T)) {
    Tree<T>* tmp = new Tree<T>;
    DynamicArray<T> arr = PreOrder();

    for (int i = 0; i < arr.GetSize(); i++)
    {
//      arr[i] = func(arr[i]);
        (*tmp).Insert(func(arr[i]));
    }
    return tmp;
}

template< typename T >
Tree<T>* Tree<T>::Where(bool (*func)(T)){
    Tree<T>* tmp = new Tree<T>;
    DynamicArray<T> arr = PreOrder();

    for (int i = 0; i < arr.GetSize(); i++)
    {
        //      arr[i] = func(arr[i]);
        if(func(arr[i]))
            (*tmp).Insert(arr[i]);
    }
    return tmp;
}

template< typename T >
Tree<T>* Tree<T>::NewTree(/*Node<T>* node*/const T& data) {//доработать
    DynamicArray<T> arr;
    Tree<T>* tmp = new Tree<T>;


    Node<T>* curr = root;
    while (curr && curr->item != data)
    {
        if (curr->item > data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (curr != NULL) {
        PreOrderNode(curr, &arr);
        for (int i = 0; i < arr.GetSize(); i++)
        {
            (*tmp).Insert(arr[i]);
        }
    }

    return tmp;
    /*DynamicArray<T> arr;
    Tree<T>* tmp = new Tree<T>;
    Tree<T> tmp1;
    tmp1->root = node;
    arr = (*tmp).PreOrder();
    for (int i = 0; i < arr.GetSize(); i++)
    {
        (*tmp).Insert(arr[i]);
    }
    return tmp;*/
}

template< typename T >
Tree<T>* Tree<T>::merge(Tree<T> *tr) {
    Tree<T>* tmp = new Tree<T>;
    DynamicArray<T> arr1 = (*tr).PreOrder();
    DynamicArray<T> arr2 = this->PreOrder();
    for (int i = 0; i < arr1.GetSize(); i++)
    {
        (*tmp).Insert(arr1[i]);
    }
    for (int i = 0; i < arr2.GetSize(); i++)
    {
        (*tmp).Insert(arr2[i]);
    }
    return tmp;
}

template< typename Type >
Type max(const Type& left, const Type& right)
{
    return left > right ? left : right;
}
