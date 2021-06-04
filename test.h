//
// Created by Pascal on 01.06.2021.
//

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
    for (int i = 0; i < 100000; i++){

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
    auto root = new Node<int>();
    *root = Node<int>(0);
    root->addChild(2);
    root->printNode();
    auto Tree = new BinaryTree<int>(root);

    delete root;
    Tree->printTree3();
    return 1;
}


int getNumberOfNodesTest(){
    auto *root = new Node<int>(0);

    int counter = getRandomLength();
    int startNumber = getRandomIntNumber();
    for (int i = 1; i < counter; i++)
        root->addChild(i);

    auto *Tree = new BinaryTree<int>(root);
        if (Tree->getNumberOfNodes(root) != counter)
            return 0;
        delete Tree;

    return 1;
}

int isSubTreeTest(){
    for (int i = 0; i < 1; i++){
        auto *root = new Node<int>();
        *root = Node<int>(getRandomIntNumber());
        auto *Tree = new BinaryTree<int>;
        int counter = getRandomIntNumber();
        int length = getRandomLength();
        int rootSubTree = getRandomIntNumber();
        int randomIndex = getRandomIntNumber() % length;
        for (int j = 0; j < length; j++){
            if (j == randomIndex){
                root->addChild(rootSubTree);
                continue;
            }
            root->addChild(getRandomIntNumber());
        }
        *Tree = BinaryTree<int>(root);
        BinaryTree<int>newTree = *(Tree->getSubTree(rootSubTree));
        if (not Tree->isSubTree(&newTree))
            return 0;
        delete Tree;
    }
    return 1;
}

int getRootTest(){

    for (int i = 0; i < 100000; i++){
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

int binaryTreeMapTest(int func(int)){
    for (int i = 0; i < 100000; i++){
        auto *root = new Node<int>();
        *root = Node<int>(getRandomIntNumber());
        auto *Tree = new BinaryTree<int>;
        int length = getRandomLength();
        for (int j = 0; j < length; j++)
            root->addChild(getRandomIntNumber());
        *Tree = BinaryTree<int>(root);

        BinaryTree<int>mappedTree = *Tree;
        mappedTree.map(func, mappedTree.getRoot());
        mappedTree.printTree3();
        Tree->printTree3();
        return 0;
    }
    return 1;
}

void binaryTreeTest(){
//    if (addChildTest())
//        cout << "Adding child to binary tree passed" << endl;
//    else
//        cout << "Adding child to binary tree failed" << endl;

    if (deleteNodeTest())
        cout << "Deleting node from binary tree passed" << endl;
    else
        cout << "Deleting node from binary tree failed" << endl;

//    if (getNumberOfNodesTest())
//        cout << "GetNumberOfNodesTest node from binary tree passed" << endl;
//    else
//        cout << "GetNumberOfNodesTest node from binary tree failed" << endl;
//
//    if (isSubTreeTest())
//        cout << "Subtree test passed" << endl;
//    else
//        cout << "Subtree test failed" << endl;
//
//    if (getRootTest())
//        cout << "Getting root test passed" << endl;
//    else
//        cout << "Getting root test failed" << endl;
//
//    if (binaryTreeMapTest(funcMultIn100Times))
//        cout << "Binary Tree map test passed" << endl;
//    else
//        cout << "Binary Tree map test failed" << endl;

}

int addElementsHeapTest(){
    for (int i = 0; i < 100000; i++){
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
    for (int i = 0; i < 10000; i++){
        Heap<int>heap;
        int length = getRandomLength();
        for (int j = 0; j < length; j++) {
            heap.addNode(getRandomIntNumber());
        }
        int counter = 0;
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


void heapTest(){
    if (addElementsHeapTest())
        cout << "Adding elements to heap passed" << endl;
    else
        cout << "Adding child to heap failed" << endl;



    if (deleteElementsHeapTest())
        cout << "Deleting elements from heap passed" << endl;
    else
        cout << "Deleting elements from heap failed" << endl;
//
//    if (getNumberOfNodesTest())
//        cout << "GetNumberOfNodesTest node from binary tree passed" << endl;
//    else
//        cout << "GetNumberOfNodesTest node from binary tree failed" << endl;

}










#endif //LAB3_TEST_H
