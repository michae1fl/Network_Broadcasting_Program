#ifndef ARRAY_HEAP_PROF_PROJ6_H
#define ARRAY_HEAP_PROF_PROJ6_H

#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class ArrayHeap {
public:
    ArrayHeap();
    ArrayHeap(ArrayHeap<T> const &h);
    ~ArrayHeap();

    ArrayHeap<T> const &operator=(ArrayHeap<T> const &ah);

    int insert(T const &item);
    void removeMinItem();
    T const &getMinItem() const;
    int getNumItems() const;

    bool isOnHeap(int key) const;
    void changeItemAtKey(int key, T const &newItem);

private:
    T *data;
    int *heapAndFreeStack;
    int *dataToHeap;

    int numItems;
    int capacity;

    void doubleCapacity();
    void bubbleUp(int ndx);
    void bubbleDown(int ndx);
};

template<typename T>
ArrayHeap<T>::ArrayHeap() {
    numItems = 0;
    capacity = 5;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];

    for (int i = 0; i < capacity; i ++) {
        heapAndFreeStack[i] = i;
    }
}

template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    numItems = h.numItems;
    capacity = h.capacity;
    data = new T[this->capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];

    for(int i = 0; i < capacity; ++i){
        data[i] = h.data[i];
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
        dataToHeap[i] = h.dataToHeap[i];
    }
}

template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    delete [] this->data;
    delete [] this->heapAndFreeStack;
    delete [] this->dataToHeap;

    data = NULL;
    heapAndFreeStack = NULL;
    dataToHeap = NULL;

    numItems = 0;
    capacity = 5;
}

template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if(this != &ah){
        delete [] this->data;
        delete [] this->heapAndFreeStack;
        delete [] this->dataToHeap;

        numItems = ah.numItems;
        capacity = ah.capacity;
        data = new T[this->capacity];
        heapAndFreeStack = new int[this->capacity];
        dataToHeap = new int[this->capacity];

        for(int i = 0; i < capacity; ++i){
            data[i] = ah.data[i];
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            dataToHeap[i] = ah.dataToHeap[i];
        }
    }
    return *this;
}

template <typename T>
int ArrayHeap<T>::insert(T const &item){
    int key;

    if(numItems == capacity){
        doubleCapacity();
    }

    data[heapAndFreeStack[numItems]] = item;

    dataToHeap[heapAndFreeStack[numItems]] = numItems;

    key = heapAndFreeStack[numItems];

    numItems++;
    bubbleUp(numItems-1);

    return key;
}

template <typename T>
void ArrayHeap<T>::removeMinItem(){
    if(numItems > 0) {

        swap(dataToHeap[heapAndFreeStack[0]],
             dataToHeap[heapAndFreeStack[numItems-1]]);

        swap(heapAndFreeStack[0],heapAndFreeStack[numItems-1]);

        numItems--;
        bubbleDown(0);
    }
    else {
        return;
    }
}

template <typename T>
T const &ArrayHeap<T>::getMinItem() const{
    return data[heapAndFreeStack[0]];
}

template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return numItems;
}

template <typename T>
bool ArrayHeap<T>::isOnHeap(int key) const {
    bool isFound = false;

    if (0 <= key && key < capacity) {
        if (0 <= dataToHeap[key] && dataToHeap[key] < numItems) {
            if (heapAndFreeStack[key] == key){
                isFound = true;
            }
        }
    }
    return isFound;
}

template <typename T>
void ArrayHeap<T>::changeItemAtKey(int key, T const &newItem){
    if(isOnHeap(key)){
        data[key] = newItem;

        bubbleUp(dataToHeap[key]);

        bubbleDown(dataToHeap[key]);
    }
}

template <typename T>
void ArrayHeap<T>::doubleCapacity(){

    int newCapacity = capacity*2;

    T *tempData = new T[newCapacity];
    int *tempHeapFreeStack = new int[newCapacity];
    int *tempDataToHeap = new int[newCapacity];

    for(int i = 0; i < capacity; ++i){
        tempData[i] = data[i];
        tempHeapFreeStack[i] = heapAndFreeStack[i];
        tempDataToHeap[i] = dataToHeap[i];
    }

    for(int i = capacity; i < newCapacity; ++i){
        tempHeapFreeStack[i] = i;
    }

    capacity *= 2;
    delete [] this->data;
    delete [] this->heapAndFreeStack;
    delete [] dataToHeap;

    data = tempData;
    heapAndFreeStack = tempHeapFreeStack;
    dataToHeap = tempDataToHeap;
}

template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx) {
    int parent = floor(ndx - 1) / 2;

    if (ndx <= 0 || parent < 0) {
        return;
    }

    if (data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]) {
        swap(heapAndFreeStack[ndx], heapAndFreeStack[parent]);
        swap(dataToHeap[heapAndFreeStack[ndx]],
             dataToHeap[heapAndFreeStack[parent]]);
        bubbleUp(parent);
    }
}

template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int child1 = 2 * ndx + 1;
    int child2 = 2 * ndx + 2;
    int least = child1;

    if(child1 >= numItems){
        return;
    }

    if(child2 < numItems){

        if(data[heapAndFreeStack[child2]] < data[heapAndFreeStack[child1]]){
            least = child2;
        }
    }


    if(data[heapAndFreeStack[least]] < data[heapAndFreeStack[ndx]]){
        swap(heapAndFreeStack[ndx],heapAndFreeStack[least]);

        swap(dataToHeap[heapAndFreeStack[ndx]],
             dataToHeap[heapAndFreeStack[least]]);
        bubbleDown(least);
    }
}

#endif
