#pragma once
// Реализация очередей с приоритетом в  C++

#include <iostream>
#include <vector>
#include "IDictionary.h"
#include "Sequence.h"
using namespace std;

template <typename T>
void swap(T* a, T* b) {
    T temp = *b;
    *b = *a;
    *a = temp;
}

template <typename T>
class PriorytyQueue
{
private:
    ArraySequence<T> queue;

public:
    PriorytyQueue() {
        queue = ArraySequence<T>();
    }
    ~PriorytyQueue() {

    }

    ArraySequence<T> GetSequence() {
        return queue;
    }

    void heapify( int i);
    void insert( T newNum);
    void deleteNode( T num);
    void printArray();
};




template <typename T>
void PriorytyQueue<T>::heapify( int i) {
    int size = queue.GetSize();

    
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && queue[l] > queue[largest])
        largest = l;
    if (r < size && queue[r] > queue[largest])
        largest = r;


    if (largest != i) {
        swap<T>( &(queue[i]),  &(queue[largest]));
        heapify(largest);
    }
}

template <typename T>
void PriorytyQueue<T>::insert( T newNum) {
    int size = queue.GetSize();
    if (size == 0) {
        queue.Append(newNum);
    }
    else {
        queue.Append(newNum);
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }
}

template <typename T>
void PriorytyQueue<T>::deleteNode(T num) {
    int size = queue.GetSize();
    int i;
    for (i = 0; i < size; i++) {
        if (num == queue[i])
            break;
    }
    swap<T>( &(queue[i]),  &(queue[size - 1]));

    queue.DelEnd();
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(i);
    }
}

template <typename T>
void PriorytyQueue<T>::printArray() {
    for (int i = 0; i < queue.GetSize(); ++i)
        cout << queue[i] << " ";
    cout << "\n";
}
