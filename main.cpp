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

    auto *node = new Node<int>;
    *node = Node<int>(2);
    node->addChild(3, node);
    node->addChild(4, node);


    auto *node2 = new Node<int>(1);
    auto* newTree= new BinaryTree<int>(node2);
    node2->addChild(10, node2);
    node2->addChild(4, node2);
    node2->addChild(3, node2);
    newTree->printTree3();
    node2->addChild(5, node2);
    node2->addChild(1, node2);
    node2->addChild(0, node2);
    node2->addChild(-5, node2);
    node2->addChild(-7, node2);
    node2->addChild(-3, node2);
    node2->addChild(-1, node2);
    node2->addChild(-100, node2);

    binaryTreeTest();




































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
