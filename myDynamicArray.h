
#ifndef LAB2_MYDYNAMICARRAY_H
#define LAB2_MYDYNAMICARRAY_H
#include "cstring"
#include <string>
#include <iostream>
#include "indexOutOfRange.h"

template<class T>
void arrCopy(T *arr_in, T *arr_out, int count);

template <class T>
class myDynamicArray {
private:
    T *arr;
    int elementSize;
    int len;

public:

    myDynamicArray(T *items, int count) {
        arr = nullptr;
        elementSize = 0;
        len = 0;
        if (count < 0) {return;}
        resize(count);

        for (int i = 0; i < len; i++) {
            arr[i] = items[i];
        }
    }

    explicit myDynamicArray(int newSize) {
        elementSize = 0;
        arr = nullptr;
        len = 0;
        if (newSize <= 0) {len = 0; return;}
        resize(newSize);
    }

    myDynamicArray() {
        arr = nullptr;
        len = 0;
        elementSize = 0;
    }

    myDynamicArray(const myDynamicArray<T> &dynamicArray) {
        arr = nullptr;
        elementSize = 0;
        len = 0;
        if (dynamicArray.len == 0) {
            return;
        }
        resize(dynamicArray.len);

        for (int i = 0; i < len; i++) {
            arr[i] = dynamicArray.arr[i];
        }
    }

    explicit myDynamicArray(myDynamicArray<T> *dynamicArray) {
        len = dynamicArray->len;
        arr = dynamicArray->arr;
        elementSize = dynamicArray->elementSize;
    }

    ~myDynamicArray() {
        delete[] arr;
    }

    int getLength() {
        return len;
    }

    T get(int index) {
        return (*this)[index];
    }

    int getSize() {
        return elementSize;
    }

    void reverse() {
        for (auto i = 0; i < len / 2; i++) {
            int index = len - 1 - i;
            T item = arr[i];
            arr[i] = arr[index];
            arr[index] = item;
        }
    }

    T &operator [] (int index) {
        if (index < 0 || index >= len)
            throw IndexOutOfRange();
        return arr[index];
    }

    myDynamicArray<T> &operator = (myDynamicArray<T> dynamicArray) {
        resize(dynamicArray.len);
        for (int i = 0; i < len; i++) {
            arr[i] = dynamicArray.arr[i];
        }
        return *this;
    }

    myDynamicArray<T> &operator = (myDynamicArray<T> *dynamicArray) {
        arr = dynamicArray->arr;
        len = dynamicArray->len;
        elementSize = dynamicArray->elementSize;

        return *this;
    }

    myDynamicArray<T> &operator* () {
        return *this;
    }

    int operator == (myDynamicArray<T> dynamicArray) {
        if (len != dynamicArray.getLength())
            return 0;

        for (int i = 0; i < len; i++) {
            if (arr[i] != dynamicArray.arr[i])
                return 0;
        }
        return 1;
    }

    T *begin() const {
        return arr;
    }

    T *end() const {
        return arr ? arr + len : nullptr;
    }

    void set(T item, int index) {
        if (index < 0 || index >= len)
            throw IndexOutOfRange();

        arr[index] = item;
    }

    void resize(int newSize) {
        if (newSize < 0)
            throw IndexOutOfRange();
        if (len == newSize) return;
        if (newSize == 0) {
            if (arr != nullptr)
                delete[] arr;
            len = 0;
            elementSize = 0;
            arr = nullptr;
            return;
        }
        if (newSize > elementSize) {
            if (elementSize == 0) elementSize = 1;
            for (elementSize; elementSize <= newSize + 1; elementSize *= 2);
            int newSize2 = newSize;
            T *arrNew = new T[elementSize];
            if (arr != nullptr) {
                arrCopy<T>(arrNew, arr, len);
                delete[] arr;
            }
            newSize = newSize2;
            arr = arrNew;
        }
        else if (newSize < elementSize / 3) {
            for (elementSize; elementSize / 3 > newSize + 1; elementSize /= 2);
            T *arrNew = new T[elementSize];
            if (arr != nullptr) {
                arrCopy<T>(arrNew, arr, newSize);
                delete[] arr;
            }
            arr = arrNew;
        }
        len = newSize;
    }
};


template<class T>
void arrCopy(T *arr_in, T *arr_out, int count) {
    for (int i = 0; i < count; i++) {
        arr_in[i] = arr_out[i];
    }
}





















#endif //LAB2_MYDYNAMICARRAY_H
