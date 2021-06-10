
#ifndef LAB2_MYARRAYSEQUENCE_H
#define LAB2_MYARRAYSEQUENCE_H


#include "myDynamicArray.h"
#include "indexOutOfRange.h"

template<class T>
class myArraySequence {
private:
    myDynamicArray<T> dynamicArray;
public:

    myArraySequence(T* items, int count) {
        dynamicArray = myDynamicArray<T> (items, count);
    }

    myArraySequence() {
        dynamicArray = myDynamicArray<T>();
    }

    explicit myArraySequence(T item) {
        dynamicArray = myDynamicArray<T>(&item, 1);
    }

    myArraySequence(const myArraySequence<T> &array) {
        dynamicArray = array.dynamicArray;
    }

    explicit myArraySequence(const myDynamicArray<T> &array) {
        dynamicArray = array;
    }

    T getFirst() {
        if (getLength() == 0)
            throw IndexOutOfRange();
        return dynamicArray[0];
    }

    T getLast() {
        if (getLength() == 0)
            throw IndexOutOfRange();
        return dynamicArray[dynamicArray.getLength() - 1];
    }

    T get(int index) {
        if (index < 0 || index >= getLength())
            throw IndexOutOfRange();
        return dynamicArray.get(index);
    }

    void set(T item, int index) {
        if (index < 0 || index >= getLength())
            throw IndexOutOfRange();
        dynamicArray.set(item, index);
    }

    T pop() {
        if (dynamicArray.getLength() == 0)
            throw IndexOutOfRange();


        T item = dynamicArray[dynamicArray.getLength() - 1];
        dynamicArray.resize(dynamicArray.getLength() - 1);

        return item;
    }

    T pop(int index) {
        if (index < 0 || index >= dynamicArray.getLength())
            throw IndexOutOfRange();

        T item = dynamicArray[index];
        for (int i = index; i < dynamicArray.getLength() - 1; i++) {
            dynamicArray[i] = dynamicArray[i+1];
        }
        dynamicArray.resize(dynamicArray.getLength() - 1);
        return item;
    }

    T &operator [] (int index) {
        if (index < 0 || index >= getLength())
            throw IndexOutOfRange();
        return dynamicArray[index];
    }

    T *begin() const {
        return dynamicArray.begin();
    }

    T *end() const {
        return dynamicArray.end();
    }

    myArraySequence<T> &operator = (myArraySequence<T> arraySequence) {
        dynamicArray = arraySequence.dynamicArray;
        return *this;
    }

    myArraySequence<T> *operator*() {
        return this;
    }

    int operator == (myArraySequence<T> arraySequence) {
        return dynamicArray == arraySequence.dynamicArray;
    }


    int getLength() {
        return dynamicArray.getLength();
    }

    void append(T item) {
        dynamicArray.resize(dynamicArray.getLength() + 1);
        dynamicArray[getLength() - 1] = item;
    }

    void append(T *item) {
        append(*item);
    }

    void prepend(T item) {
        dynamicArray.resize(dynamicArray.getLength() + 1);
        for (int i = dynamicArray.getLength() - 2; i >= 0; i--) {
            dynamicArray[i+1] = dynamicArray[i];
        }
        dynamicArray[0] = item;
    }

    void prepend(T *item) {
        prepend(*item);
    }

    void remove() {
        dynamicArray.resize(0);
    }


    void insert(T item, int index) {
        if (index < 0 || index >=dynamicArray.getLength())
            throw IndexOutOfRange();
        dynamicArray.resize(dynamicArray.getLength() + 1);
        for (int i = dynamicArray.getLength() - 2; i >= index; i--) {
            dynamicArray[i+1] = dynamicArray[i];
        }
        dynamicArray[index] = item;
    }

    void insert(T *item, int index) {
        insert(*item, index);
    }

};



#endif //LAB2_MYARRAYSEQUENCE_H
