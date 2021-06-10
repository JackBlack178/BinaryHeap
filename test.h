
#ifndef LAB3_TEST_H
#define LAB3_TEST_H
#include "myBinaryHeap.h"
#include "myBinaryTree.h"
#include "iostream"
using std::cout;
using std::endl;

int getRandomIntNumber(){
    return rand();
}

int getRandomIntNumberInRange(int up){
    return getRandomIntNumber() % up;

}

int getRandomLength(int maxLength = 100){
    while(true){
        int number = getRandomIntNumber();
        if (number % maxLength != 0)
            return number % maxLength;
    }
}

int funcMultIn100Times(int number){
    return number * 100;
}

int addChildTest(){
    for (int i = 0; i < 1000000; i++){

        int number1 = getRandomIntNumber();
        int number2 = getRandomIntNumber();
        Node<int>node{number1};
        node.addChild(number2);

        if (number1 > number2){
            if (node.getLeftChild() == nullptr or node.getLeftChild()->getData() != number2)
                return 0;
        }

        if (number1 < number2){
            if (node.getRigthChild() == nullptr or node.getRigthChild()->getData() != number2)
                return 0;
        }
    }
    return 1;
}



int deleteNodeTest(){
    for (int i = 0; i < 1000000; i++){
        int startNumber = getRandomIntNumber();
        auto root = new Node<int>(startNumber);
        int length = getRandomLength();
        for (int j = 1; j < length; j++)
            root->addChild(startNumber + j);
        auto Tree = new BinaryTree<int>(root);

        Tree->deleteNode(startNumber);
        if (Tree->getNumberOfNodes() != 0)
            return 0;
        delete Tree;
    }
    return 1;
}


int getNumberOfNodesTest(){
    for (int j = 0; j < 1000000; j++){
        auto *root = new Node<int>(0);
        int counter = getRandomLength();
        int startNumber = getRandomIntNumber();
        for (int i = 1; i < counter; i++)
            root->addChild(i);

        auto *Tree = new BinaryTree<int>(root);
        if (Tree->getNumberOfNodes() != counter)
            return 0;
        delete Tree;
    }
    return 1;
}

int isSubTreeTest(){
    for (int i = 0; i < 1000000; i++){
        BinaryTree<int>Tree1(getRandomIntNumber());
        int subRoot = getRandomIntNumber();
        int length = getRandomLength();
        for (int j = 0; j < length; j++){
            Tree1.addNode(getRandomIntNumber());
        }
        Tree1.addNode(subRoot);
       BinaryTree<int>Tree2  = *Tree1.getSubTree(subRoot);
        if (Tree1.isSubTree(&Tree2)) {
            return 0;
        }
    }
    return 1;
}

int getRootTest(){

    for (int i = 0; i < 1000000; i++){
        auto *root = new Node<int>();
        *root = Node<int>(getRandomIntNumber());
        auto *Tree = new BinaryTree<int>;
        int length = getRandomLength();
        for (int j = 0; j < length; j++)
            root->addChild(getRandomIntNumber());
        *Tree = BinaryTree<int>(root);

        if (Tree->getRoot() != root)
            return 0;
    }
    return 1;

}


int checkMap(int func(int), Node<int>* node, Node<int>* mapNode){
    if (func(node->getData()) != mapNode->getData())
        return 0;
    if (node->getLeftChild() != nullptr and node->getRigthChild() != nullptr)
        return checkMap(func,node->getLeftChild(), mapNode->getLeftChild()) and checkMap(func, node->getRigthChild(), mapNode->getRigthChild());

    if (node->getLeftChild() != nullptr)
        return checkMap(func,node->getLeftChild(), mapNode->getLeftChild());

    if (node->getRigthChild() != nullptr)
        return checkMap(func,node->getRigthChild(), mapNode->getRigthChild());
    return 1;

}

int binaryTreeMapTest(int func(int)){
    for (int i = 0; i < 10000; i++){
        BinaryTree<int>Tree(getRandomIntNumber());
        int length = getRandomLength();
        for (int j = 1; j < length; j++)
            Tree.addNode(getRandomIntNumber());

        BinaryTree<int>mappedTree(Tree);
        mappedTree.map(funcMultIn100Times);
        if (not checkMap(funcMultIn100Times, Tree.getRoot(), mappedTree.getRoot()))
            return 0;

    }
    return 1;
}

void binaryTreeTest(){
    cout << "Binary tree tests\n";
    if (addChildTest())
        cout << "Adding child to binary tree passed" << endl;
    else
        cout << "Adding child to binary tree failed" << endl;

    if (deleteNodeTest())
        cout << "Deleting node from binary tree passed" << endl;
    else
        cout << "Deleting node from binary tree failed" << endl;

    if (getNumberOfNodesTest())
        cout << "GetNumberOfNodesTest node from binary tree passed" << endl;
    else
        cout << "GetNumberOfNodesTest node from binary tree failed" << endl;

    if (isSubTreeTest())
        cout << "Subtree test passed" << endl;
    else
        cout << "Subtree test failed" << endl;

    if (getRootTest())
        cout << "Getting root test passed" << endl;
    else
        cout << "Getting root test failed" << endl;

    if (binaryTreeMapTest(funcMultIn100Times))
        cout << "Binary Tree map test passed" << endl;
    else
        cout << "Binary Tree map test failed" << endl;

}

int addElementsHeapTest(){
    for (int i = 0; i < 1000000; i++){
        Heap<int>heap;
        int length = getRandomIntNumber() % 100;
        for (int j = 0; j < length; j++) {
            heap.addNode(getRandomIntNumber());
        }
        if (heap.getSize() != length)
            return 0;
    }
    return 1;

}

int deleteElementsHeapTest(){
    for (int i = 0; i < 1000; i++){
        Heap<int>heap;
        int length = getRandomLength();
        for (int j = 0; j < length; j++) {
            heap.addNode(getRandomIntNumber());
        }
        int numberOfPeopleToDelete = getRandomIntNumber() % length;
        for (int j = 0; j < numberOfPeopleToDelete; j++){

            int numberToDelete = getRandomIntNumber();
            int indexNumberToDelete = heap.find(numberOfPeopleToDelete);
            if (indexNumberToDelete == -1)
                continue;
            heap.deleteElement(numberToDelete);
            if (heap.find(numberToDelete) != -1)
                return 0;
        }
    }
    return 1;
}

int getMaxNumberTest(){
    for (int i = 0; i < 1000000; i++){
        Heap<int>heap;
        int length = getRandomLength();
        for (int j = 0; j < length; j++) {
            heap.addNode(getRandomIntNumber());
        }
        int maxNumber = heap[0];
        for (int j = 0; j < length; j++){
            if (maxNumber < heap[j])
                maxNumber = heap[j];
        }
        if (heap.getmaxNumber() != maxNumber)
            return 0;
    }
    return 1;
}

int getSubHeapTest(){
    for (int i = 0; i < 1000000; i++){
        Heap<int>heap;
        int length = getRandomLength();
        int subHeapRoot = getRandomIntNumber();
        for (int j = 1; j < length; j++) {
            heap.addNode(getRandomIntNumber());
        }
        heap.addNode(subHeapRoot);
        Heap<int>subHeap = heap.getSubHeap(subHeapRoot);
        if (not heap.isSubHeap(subHeap))
            return 0;
    }
    return 1;
}

int isHeapTheSameTest(){
    for (int i = 0; i < 1000000; i++){
        Heap<int>heap;
        int length = getRandomLength();

        for (int j = 0; j < length; j++) {
            heap.addNode(getRandomIntNumber());
        }
        Heap<int>heap2;
        for (int j = 0; j < length; j++) {
            heap2.addNode(heap[j]);
        }
        if (not heap.isHeapTheSame(heap,heap2))
            return 0;
    }
    return 1;
}

void heapTest(){
    cout << "\nBinary heap tests\n";

    if (addElementsHeapTest())
        cout << "Adding elements to heap passed" << endl;
    else
        cout << "Adding child to heap failed" << endl;

    if (deleteElementsHeapTest())
        cout << "Deleting elements from heap passed" << endl;
    else
        cout << "Deleting elements from heap failed" << endl;

    if (getMaxNumberTest())
        cout << "Getting max number test passed" << endl;
    else
        cout << "Getting max number test failed" << endl;

    if (getSubHeapTest())
        cout << "Getting subheap passed" << endl;
    else
        cout << "GGetting subheap test failed" << endl;

    if (isHeapTheSameTest())
        cout << "Heap the same test passed" << endl;
    else
        cout << "Heap the same test test failed" << endl;
}



#endif //LAB3_TEST_H
