//
// Created by Pascal on 02.06.2021.
//

#ifndef LAB3_MENU_H
#define LAB3_MENU_H

#include "myBinaryTree.h"

BinaryTree<int>* createTree(){
    auto *node = new Node<int>;
    *node = Node<int>(0);

    for (int i = 0; i < 5; i++)
        node->addChild(rand() % 10);
    auto* Tree = new BinaryTree<int>(node);
    return Tree;
}

void menu(){

}


#endif //LAB3_MENU_H
