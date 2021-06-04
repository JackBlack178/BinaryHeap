#include "myBinaryTree.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
#include "myBinaryHeap.h"
#include "test.h"
#include "menu.h"

int func2(int value){
    return value * 2;
}


int main() {
//    auto *node = new Node<int>(2);
//    node->addChild(3);
//    node->addChild(4);
//    node->addChild(2);
//    node->addChild(10);
//    node->addChild(3);
//    BinaryTree<int>newTree(node);
//    newTree.printTree3();
//
//    newTree.deleteNode(3);
//    newTree.addNode(10);
//    int number = 10;
//    newTree.find(number);
//    binaryTreeTest();

    auto node = new Node<int>(0);
    node->addChild(5);
    BinaryTree<int>tree(node);
    tree.deleteNode(5);
    node->getInfo();
    node->getData();
    node->getRigthChild();


//    Heap<int>heap;
//    heap.addNode(1);
//    heap.addNode(2);
//    heap.addNode(3);
//    heap.addNode(-1);
//    heap.addNode(-5);
//    heap.addNode(-6);
//    heap.addNode(-90);
//    heap.addNode(10);
//    heap.addNode(15);
//    heap.printHeap();
//    cout << "\n";
//    Heap<int>newHeap = heap.getSubHeap(10);
//    newHeap.printHeap();
//    cout << heap.isSubHeap(newHeap)<< endl;


















    return 0;
}
