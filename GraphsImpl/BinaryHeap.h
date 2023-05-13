#pragma once

#include <iostream>
#include <vector>

template<class T>
class BinaryHeap {
private:
    const std::string EXCEPTION_DESC = "Kopiec jest pusty!";
    std::vector<T> base;
    int vertexCount;

    void heapFixUp(int index);

    void heapFixDown(int index);

public:
    explicit BinaryHeap();

    ~BinaryHeap();

    void insert(T element);

    void updateQueue(T existing, T newValue);

    T pop();

    bool find(T element);

    bool isEmpty();
};

template<class T>
BinaryHeap<T>::BinaryHeap() {
    vertexCount = 0;
}

template<class T>
BinaryHeap<T>::~BinaryHeap() = default;

template<class T>
void BinaryHeap<T>::insert(T element) {
    //Standardowe dodanie elementu do kopca.
    int index = vertexCount;
    vertexCount++;
    base.push_back(element);
    heapFixUp(index);
}

template<class T>
void BinaryHeap<T>::updateQueue(T existing, T newValue) {
    for (int i = 0; i < vertexCount; i++) {
        //Jeśli element zostanie znaleziony, zamieniamy wartość i aktualizujemy kopiec.
        if (base[i] == existing) {
            base[i] = newValue;
            if (i == 0) {
                heapFixDown(0);
                return;
            }
            T parent = base[(i - 1) / 2];
            if (base[i] < parent) heapFixUp(i);
            else heapFixDown(i);
            return;
        }
    }
}

template<class T>
T BinaryHeap<T>::pop() {
    if (vertexCount == 0) throw std::length_error(EXCEPTION_DESC);
    vertexCount--;

    //Zapisujemy wartość szczytu kopca i usuwamy go.
    T root = base[0];
    base[0] = base[vertexCount];
    base.erase(base.begin() + vertexCount);
    heapFixDown(0);
    return root;
}

template<class T>
void BinaryHeap<T>::heapFixUp(int index) {
    //Standardowa naprawa kopca w górę.
    int parent = (index - 1) / 2;
    T fixVertex = base[index];
    while (index > 0 && base[parent] > fixVertex) {
        T temp = base[index];
        base[index] = base[parent];
        base[parent] = temp;
        index = parent;
        parent = (index - 1) / 2;
    }
}

template<class T>
void BinaryHeap<T>::heapFixDown(int index) {
    //Standardowa naprawa kopca w dół.
    T fixVertex = base[index];
    int greaterChildren = 2 * index + 1;
    while (greaterChildren < vertexCount) {
        if (greaterChildren + 1 < vertexCount && base[greaterChildren] > base[greaterChildren + 1]) greaterChildren++;
        if (fixVertex <= base[greaterChildren]) break;
        T temp = base[index];
        base[index] = base[greaterChildren];
        base[greaterChildren] = temp;
        index = greaterChildren;
        greaterChildren = 2 * greaterChildren + 1;
    }
}

template<class T>
bool BinaryHeap<T>::find(T element) {
    for (int i = 0; i < vertexCount; i++) {
        if (base[i] == element) return true;
    }
    return false;
}

template<class T>
bool BinaryHeap<T>::isEmpty() {
    return vertexCount == 0;
}