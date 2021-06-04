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
    auto node = new Node<int>(1);
    Node<int>* newNode;
    node->addChild(5);
    node->addChild(-2);
    node->addChild(7);
    node->addChild(9);
    node->addChild(8);
    node->addChild(-2);
    node->addChild(11);
    node->addChild(15);
    node->getInfo();
    newNode = node->getLeftChild();
    delete newNode;
    newNode->getData();
    node->getInfo();




//    auto node = new Node<int>(2);
//    node->addChild(4);
//    node->addChild(16);
//    node->addChild(1);
//    node->addChild(0);
//    node->printNode();
//    auto Tree = new BinaryTree<int>;
//    *Tree = BinaryTree<int>(node);
//    Tree->printTree();






















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
