//
// Created by Pascal on 31.05.2021.
//

#ifndef LAB3_MYBINARYHEAP_H
#define LAB3_MYBINARYHEAP_H

#include "myArraySequence.h"

template <class T>
class Heap {
    myArraySequence<T> elements;
    int heapSize = 0;

    void addFromArray(Heap<T>* heap ,myArraySequence<T> array, int index){
        heap->elements.append(array.get(index));

        if (2*index+1 < heapSize)
            addFromArray(heap, array, 2*index+1);

        if (2*index+2 < heapSize){
            addFromArray(heap, array, 2*index+2);
        }
    }

    int deleteBranch(int index){
        int counter = 1;
        if (2*index + 1 < elements.getLength()){
            counter += deleteBranch(2*index+1);
            counter++;

        }
        if (2*index + 2 < elements.getLength()){
            counter = deleteBranch(2*index+2);
            counter++;
        }

        elements.set(elements.get(elements.getLength()-counter), index);
        return counter;
    }

public:
    Heap() = default;

    Heap(const Heap& heap){
        heapSize = heap.heapSize;
        elements = heap.elements;
    };

    explicit Heap(const myArraySequence<T> &array){
        elements = myArraySequence<T>(array);
        heapSize = array.getLength();
        for (int i = heapSize / 2; i >= 0; i--)
            heapify(i);
    }

    int getSize(){
        return heapSize;
    }


    void addNode(int element){

        int i, parent;
        i = heapSize;
        elements.append(element);
        parent = (i-1)/2;
        while(parent >= 0 && i > 0)  {
            if(elements[i] > elements[parent]) {
                int temp = elements[i];
                elements[i] = elements[parent];
                elements[parent] = temp;
            }
            i = parent;
            parent = (i-1)/2;
        }
        heapSize++;
        for (int j = 0; j < heapSize; j++)
            heapify(i);
    };

    int find(T value){
        for (int index = 0; index < heapSize; index++){
            if (elements.get(index) == value)
                return index;
        }
        return -1;
    }

    void deleteElement(T value){
        int index = find(value);
        if (index == -1)
            return;

        if (2*index+1 > heapSize or 2*index+2 > heapSize) //Условие того, что будем удалять узел у которого есть дети
            return;


        elements.set(elements.getLast(), index);

        elements.pop();

        heapSize = elements.getLength();

        for (int i = 0; i < heapSize/2; i++)
            heapify(i);
    }

    Heap<T>& operator = (const Heap<T>&heap){
        heapSize = heap.heapSize;
        elements = heap.elements;
        return *this;
    }

    int operator == (Heap<T>heap){
        return heap.heapSize == heapSize and heap.elements == elements;
    }

    int isTreeTheSame(Heap<T>heap1, Heap<T>heap2){
        if (heap1.heapSize != heap2.heapSize or heap1.heapSize == 0 or heap2.heapSize == 0)
            return 0;
        return heap1.elements == heap2.elements;
    }

    int operator != (Heap<T>heap){
        return !(heap == *this);
    }

    int isSubHeap(Heap<T>subHeap){
        if (subHeap.heapSize == 0)
            return 0;
        Heap<T>childHeap = getSubHeap(subHeap.elements[0]);
        return isTreeTheSame(childHeap, subHeap);
    }


    void printHeap(std::ostream& otp = std::cout){
        if (heapSize > 1 and elements[0] == elements[1] or heapSize > 2 and elements[0] == elements[2])
            return;

        int i = 0;
        int k = 1;
        while(i < heapSize) {
            while((i < k) && (i < heapSize)) {
                otp << elements.get(i) << " ";
                i++;
            }
            otp << "\n";
            k = k * 2 + 1;
        }
    }

    void heapify(int i) {
        int left, right;
        int temp;
        left = 2 * i + 1;
        right = 2 * i + 2;
        if (left < heapSize) {
            if (elements.get(i) < elements.get(left)) {
                temp = elements.get(i);
                elements[i] = elements.get(left);
                elements[left] = temp;

                heapify(left);
            }
        }
        if (right < heapSize) {
            if (elements[i] < elements[right]) {
                temp = elements[i];
                elements[i] = elements[right];
                elements[right] = temp;
                heapify(right);

            }
        }
    }

    int getmaxNumber() {
        int number;
        number = elements[0];
        elements[0] = elements[heapSize-1];
        heapSize--;
        heapify(0);
        return(number);
    }

    Heap<T> getSubHeap(T value){
        if (elements[0] == value)
            return *this;

        auto *newHeap = new Heap<T>;
        int index = find(value);
        if (index == -1)
            return *newHeap;

        newHeap->elements.append(elements.get(index));

        if (2*index+1 < heapSize){
            addFromArray(newHeap, elements, 2*index+1);
        }

        if (2*index+2 < heapSize){
            addFromArray(newHeap, elements, 2*index+2);
        }

        for (int i = 0; newHeap->getSize() / 2; i++)
            newHeap->heapify(i);
        newHeap->heapSize = newHeap->elements.getLength();
        return *newHeap;
    }

};










#endif //LAB3_MYBINARYHEAP_H
