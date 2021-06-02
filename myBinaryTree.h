//
// Created by Pascal on 30.05.2021.
//

#ifndef LAB3_MYBINARYTREE_H
#define LAB3_MYBINARYTREE_H



#include "math.h"
#include "myArraySequence.h"
#include "iostream"
using std::cout;
using std::endl;




template <class T>
class Node{
private:
    Node *left = nullptr;
    Node *rigth = nullptr;
    Node *parent = nullptr;
    T data;
    int heigth = 1;
public:
    Node(Node &node){
        *left = *node.left;
        *rigth = *node.rigth;
        *parent = *node.parent;
        data = node.data;
        heigth = node.heigth;
    }

    Node() = default;

    int nodesIsTheSame(Node<T>* node1, Node<T>* node2){
        if (node1 == nullptr and node2 != nullptr or node1 != nullptr and node2 == nullptr)
            return 0;
        if (node1 == nullptr and node2 == nullptr)
            return 1;

        if (node1->data == node2->data){
            return nodesIsTheSame(node1->getLeftChild(),node2->getLeftChild()) and nodesIsTheSame(node1->getRigthChild(),node2->getRigthChild());
        }
        return 0;
    }

    explicit Node(T data){
        left = nullptr;
        rigth = nullptr;
        parent = nullptr;
        this->data = data;
        heigth = 1;
    }

    ~Node(){
        if (left != nullptr)
        {
            delete left;
            left = nullptr;
        }

        if (rigth != nullptr){
            delete rigth;
            rigth = nullptr;
        }

    }

    Node<T>& operator = (const Node<T>& node){
        data = node.data;
        heigth = node.heigth;

        if (node.left != nullptr){
            if (left == nullptr)
                left = new Node<T>;
            *left = *node.left;
        }

        if (node.rigth != nullptr){
            if (rigth == nullptr)
                rigth = new Node<T>;
            *rigth = *node.rigth;
        }
    }

    int operator == (Node<T>& node){
        return nodesIsTheSame(this,node);
    }

    int operator != (Node<T>& node){
        return not nodesIsTheSame(this,node);
    }

    Node * getLeftChild(){
        return left;
    }

    Node * getRigthChild(){
        return rigth;
    }

    Node * getParent(){
        return parent;
    }

    T getData(){
        return data;
    }

    void setHeigth(int number){
        heigth = number;
    }

    void printNode(std::ostream& output = std::cout) {
        if (!data)
            return;
        cout << " " << data << endl;
        if (left == nullptr && rigth == nullptr)
            return;
        if (rigth == nullptr && left != nullptr) {
            cout << left->data << endl;
            return;
        }

        if (left == nullptr && rigth != nullptr) {
            cout << "   " << rigth->data << endl;
            return;}
            cout << left->data << " " << rigth->data << endl;
        }


    void addChild(T Tdata, Node<T> *node ){
        if (Tdata < node->data){
            if (node->left == nullptr){
                auto *newNode = new Node<T>;
                *newNode = Node<T>(Tdata);
                newNode->left = nullptr;
                newNode->rigth = nullptr;
                node->left = newNode;
                node->left->heigth = node->heigth+1;
                node->left->parent = node;
                return;
            }
            else
                addChild(Tdata, node->left);
        }
        if (Tdata > node->data){
            if (node->rigth == nullptr){
                auto *newNode = new Node<T>;
                *newNode = Node<T>(Tdata);
                newNode->left = nullptr;
                newNode->rigth = nullptr;
                node->rigth = newNode;
                node->rigth->heigth = node->heigth+1;
                node->rigth->parent = node;
                return;
            }
            else
                addChild(Tdata, node->rigth);
        }
    }

    void addExistingChild(Node<T> *newRoot , Node<T> *node){

        if (newRoot->getData() < node->getData()){
            if (newRoot->getRigthChild() == nullptr)
                newRoot->rigth = node;
            else
                addExistingChild(newRoot->rigth, node);
        }

        if (newRoot->getData() > node->getData()){
            if (newRoot->getLeftChild() == nullptr)
                newRoot->left = node;
            else
                addExistingChild(newRoot->left, node);
        }
    }

    int getHeigth(){
        return heigth;
    }

    void setValue(T value){
        data = value;
    }

    void setChild(int number, Node<T>* newChild){
        switch(number){
            case 1: left = newChild;
                return;
            case 2: rigth = newChild;
                return;
            default: return;
        }
    }



};

void func2(Node<int> *node){
    cout << node->getData() << endl;
}


template <class T>
class BinaryTree{
private:
    Node<T> * root;
public:

    BinaryTree( BinaryTree &tree){
        *root = *(tree.root);
    }

    explicit BinaryTree(Node<T> *node){
        root = node;
    }

    explicit BinaryTree(T data){
        auto * node = new Node<T>;
        *node = Node<T>(data);
        root = node;

    }

    BinaryTree(){
        root = nullptr;
    }

    ~BinaryTree(){
        delete root;
    }


    int operator == (BinaryTree<T>* tree){
        return root->nodesIsTheSame(root, tree->getRoot());
    }

    int operator != (BinaryTree<T>* tree){
        return not(root->nodesIsTheSame(root, tree->getRoot()));

    }

    BinaryTree<T>& operator = (const BinaryTree<T>& tree){
        if (root == nullptr)
            root = new Node<T>;
        *root = *(tree.root);
    }

    Node<T>* find(T data, Node<T>* node) const {
        if (data == node->getData())
            return node;
        if (node->getRigthChild() != nullptr && node->getData() < data)
            return find(data, node->getRigthChild());

        if (node->getLeftChild() != nullptr && node->getData() < data)
            return find(data, node->getLeftChild());

        return nullptr;
    }

    int contain(const T &data, Node<T>* node) const{
        return find(data, node) != nullptr;
    }

    void addNode(T data){
        root->addChild(data, root);
    }

    void addInArray(Node<T>* node, myArraySequence<T>*array, int index){
        array->set(node->getData(), index);

        if (node->getLeftChild() != nullptr)
            addInArray(node->getLeftChild(), array, 2*index+1);
        else
            array->set(root->getData(),2*index+1);


        if (node->getRigthChild() != nullptr)
            addInArray(node->getRigthChild(), array, 2*index+2);
        else
            array->set(root->getData(),2*index+2);
    }

    myArraySequence<T>* getArray(Node<T>* node){

        myArraySequence<T>* array = new myArraySequence<int>;
        for (int i = 0; i < pow(2,getMaxHeigth(root) + 1); i++){array->append(0);}
        addInArray(root,array,0);
        return array;
    }

    int getNumberOfNodes(Node<T>* node, int numbers = 0){
        numbers++;

        if (node->getLeftChild() == nullptr and node->getRigthChild() == nullptr)
            return numbers;

        if (node->getLeftChild() != nullptr and node->getRigthChild() != nullptr){
            return getNumberOfNodes(node->getLeftChild(), numbers) + getNumberOfNodes(node->getRigthChild(), numbers) - numbers;
        }

        if (node->getLeftChild() != nullptr){
            return getNumberOfNodes(node->getLeftChild(), numbers);
        }

        if (node->getRigthChild() != nullptr){
            return getNumberOfNodes(node->getRigthChild(), numbers);
        }

    }

    BinaryTree* getSubTree(T value, Node<T>* node){
        if (node == nullptr)
            return nullptr;

        if (node->getData() == value){
            auto newNode = new Node<T>;
            *newNode = *node;
            auto newTree = new BinaryTree<T>;
            *newTree = BinaryTree<T>(newNode);
            return newTree;
        }

        if (value > node->getData())
            return getSubTree(value, node->getRigthChild());

        if (value < node->getData())
            return getSubTree(value, node->getLeftChild());
    }



    void printTree(){
        KLPtraversal(&func2, root);
    }


    void printTree3(std::ostream& output = std::cout){
        if (root == nullptr)
            return;

        myArraySequence<T> array;
        for (int i = 0; i < pow(2,getMaxHeigth(root) + 1); i++){array.append(root->getData());}
        addInArray(root,&array,0);
        int len = array.getLength();

        int i = 0;
        int k = 1;
        while(i < pow(2,getMaxHeigth(root)+1) - 1) {
            for (int j = 0; j < getMaxHeigth(root) * 4 - k; ++j) {cout<<" ";}
            while((i < k) && (i < len)) {
                if (i != 0 and array.get(i) == root->getData())
                    cout << " ";

                else
                    cout << array.get(i) << " ";
                i++;
            }
            cout << std::endl;
            k = k * 2 + 1;
        }
    }


    Node<T>* getRoot(){
        return root;
    }

    int getMaxHeigth(Node<T>* node){
        if (node == nullptr)
            return 0;

        int tempValue1 = -1;
        int tempValue2 = -1;

        if (node->getLeftChild() != nullptr){
            tempValue1 = getMaxHeigth(node->getLeftChild());
        }
        if (node->getRigthChild() != nullptr){
            tempValue2 = getMaxHeigth(node->getRigthChild());
        }


        if (node->getLeftChild() == nullptr and node->getRigthChild() == nullptr){
            return node->getHeigth();
        }


        if (tempValue1 > tempValue2)
            return tempValue1;
        else
            return tempValue2;

    }

    int isSubTree(Node<T>* node, BinaryTree<T>* subTree){

        if (node->nodesIsTheSame(node,subTree->getRoot())) {
            return 1;
        }
        if (node->getLeftChild() != nullptr and node->getRigthChild() != nullptr){
            return isSubTree(node->getLeftChild(), subTree) || isSubTree(node->getRigthChild(), subTree);
        }

        if (node->getLeftChild() != nullptr)
            return isSubTree(node->getLeftChild(), subTree);

        if (node->getRigthChild() != nullptr)
            return isSubTree(node->getRigthChild(), subTree);

        return 0;
    }

    void deleteNode(T value, Node<T>* node){
        if (node == nullptr)
            return;

        if (value == root->getData()){
            delete root;
            root = nullptr;
            return;
        }

        if (node->getData() == value){
            if (node->getParent()->getLeftChild() == node){
                node->getParent()->setChild(1, nullptr);
            }
            else
                node->getParent()->setChild(2, nullptr);
            delete node;
            return;
        }

        if (value < node->getData() and node->getLeftChild() != nullptr)
            deleteNode(value, node->getLeftChild());

        if (value > node->getData() and node->getRigthChild() != nullptr)
            deleteNode(value, node->getRigthChild());
    }

    void KLPtraversal(void (*func)(Node<T>*), Node<T>* node){
        if (root == nullptr)
            return;
        func(node);
        if (node->getLeftChild() != nullptr)
            KLPtraversal(func, node->getLeftChild());

        if (node->getRigthChild() != nullptr)
            KLPtraversal(func, node->getRigthChild());
    }

    void KPLtraversal(void (*func)(Node<T>*), Node<T>* node){
        func(node);
        if (node->getRigthChild() != nullptr)
            KLPtraversal(func, node->getRigthChild());

        if (node->getLeftChild() != nullptr)
            KLPtraversal(func, node->getLeftChild());
    }

    void LPKtraversal(void (*func)(Node<T>*), Node<T>* node){
        if (node->getLeftChild() != nullptr)
            KLPtraversal(func, node->getLeftChild());

        if (node->getRigthChild() != nullptr)
            KLPtraversal(func, node->getRigthChild());

        func(node);
    }

    void PLKtraversal(void (*func)(Node<T>*), Node<T>* node){
        if (node->getRigthChild() != nullptr)
            KLPtraversal(func, node->getRigthChild());

        if (node->getLeftChild() != nullptr)
            KLPtraversal(node->getLeftChild());

        func(node);
    }

    void LKPtraversal(void (*func)(Node<T>*), Node<T>* node){
        if (node->getLeftChild() != nullptr)
            KLPtraversal(func, node->getLeftChild());

        func(node);

        if (node->getRigthChild() != nullptr)
            KLPtraversal(func, node->getRigthChild());
    }

    void PKLtraversal(void (*func)(Node<T>*), Node<T>* node){
        if (node->getRigthChild() != nullptr)
            KLPtraversal(func, node->getRigthChild());

        func(node);

        if (node->getLeftChild() != nullptr)
            KLPtraversal(func, node->getLeftChild());
    }


    void map(T func(T), Node<T>* node){
        if (root == nullptr)
            return;

        node->setValue(func(node->getData()));

        if (node->getLeftChild() != nullptr)
            map(func, node->getLeftChild());

        if (node->getRigthChild() != nullptr)
            map(func, node->getRigthChild());
    }


    BinaryTree<T>* where(T func(T)){
        auto newTree = new BinaryTree<T>;
        *newTree = BinaryTree<T>(root);
        addNodeWithCondition(func, this, newTree);
        return newTree;

    }

    void addNodeWithCondition( T func(T), Node<T>* node, Node<T>* newNode){
        if (node->getLeftChild() != nullptr && node->getData() == func(node->getLeftChild()->getData())){
            newNode->addExistingChild(node->getLeftChild());
            addNodeWithCondition(func, node->getLeftChild(), newNode);
        }

        if (node->getRigthChild() != nullptr && node->getData() == func(node->getRightChild()->getData())){
            newNode->addExistingChild(node->getRigthChild());
            addNodeWithCondition(func, node->getRigthChild(), newNode);
        }
    }

    T reduce(T func(T value), int battery, Node<T>* node) {
        if (root == nullptr)
            return 0;


        if (node->getLeftChild() != nullptr)
            battery = reduce(func, battery, node->getLeftChild());

        if (node->getRigthChild() != nullptr)
            battery = reduce(func, battery, node->getRigthChild());

        battery += func(node->getData());

        return battery;
    }


    int isBalanced(Node<T>* node){


        if (node->getLeftChild() == nullptr)
            return 0;

        if (node->getRigthChild() == nullptr)
            return 0;

        return abs(getMaxHeigth(node->getLeftChild()) - getMaxHeigth(node->getRigthChild())) <= 1;
    }


    BinaryTree<T>* balance(Node<T>* node){
        if (isBalanced(node)){
            if (node == root)
                return this;
            auto *newTree = new BinaryTree<T>;
            *newTree = BinaryTree<T>(node);
            return newTree;
        }

        if (getMaxHeigth(node->getLeftChild()) > getMaxHeigth(node->getRigthChild())){
            Node<T>* lastRoot = node;
            Node<T>* newRootNode = node->getLeftChild();
            if (lastRoot != nullptr)
                newRootNode->addExistingChild(newRootNode, lastRoot);
            if (newRootNode->getLeftChild() != nullptr)
                newRootNode->addExistingChild(newRootNode, newRootNode->getLeftChild());
            if (newRootNode->getRigthChild() != nullptr)
                newRootNode->addExistingChild(newRootNode, newRootNode->getRigthChild());

            return balance2(newRootNode);
        }
        if (getMaxHeigth(node->getLeftChild()) < getMaxHeigth(node->getRigthChild())){
            Node<T>* lastRoot = node;
            Node<T>* newRootNode = node->getRigthChild();
            if (lastRoot != nullptr)
                newRootNode->addExistingChild(newRootNode, lastRoot);
            if (newRootNode->getLeftChild() != nullptr)
                newRootNode->addExistingChild(newRootNode, newRootNode->getLeftChild());
            if (newRootNode->getRigthChild() != nullptr)
                newRootNode->addExistingChild(newRootNode, newRootNode->getRigthChild());

            return balance2(newRootNode);
        }
    }
};


#endif //LAB3_MYBINARYTREE_H


