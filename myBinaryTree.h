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

    int nodesIsTheSamePrivate(Node<T>* node1, Node<T>* node2){
        if (node1 == nullptr and node2 != nullptr or node1 != nullptr and node2 == nullptr)
            return 0;
        if (node1 == nullptr and node2 == nullptr)
            return 1;

        if (node1->data == node2->data){
            return nodesIsTheSamePrivate(node1->getLeftChild(),node2->getLeftChild()) and nodesIsTheSamePrivate(node1->getRigthChild(),node2->getRigthChild());
        }
        return 0;
    }

    void addChildPrivate(T Tdata, Node<T> *node ){
        if (node == nullptr){
            Node<T> newNode(Tdata);
            *node = newNode;
            return;
        }

        if (Tdata < node->data){
            if (node->left == nullptr){
                Node<T> newNode(Tdata);
                newNode.left = nullptr;
                newNode.rigth = nullptr;
                newNode.parent = node;
                newNode.heigth = node->heigth + 1;
                node->left = new Node<T>;
                *node->left = newNode;
                return;
            }
            else
                return addChildPrivate(Tdata, node->left);
        }
        if (Tdata > node->data){
            if (node->rigth == nullptr){
                Node<T> newNode(Tdata);
                newNode.left = nullptr;
                newNode.rigth = nullptr;
                newNode.parent = node;
                newNode.heigth = node->heigth + 1;
                node->rigth = new Node<T>;
                *node->rigth = newNode;
                return;
            }
            else
                return addChildPrivate(Tdata, node->rigth);
        }
    }

    void addExistingChildPrivate(Node<T> *newRoot , Node<T> *node){

        if (newRoot->getData() < node->getData()){
            if (newRoot->getRigthChild() == nullptr)
                newRoot->rigth = node;
            else
                addExistingChildPrivate(newRoot->rigth, node);
        }

        if (newRoot->getData() > node->getData()){
            if (newRoot->getLeftChild() == nullptr)
                newRoot->left = node;
            else
                addExistingChildPrivate(newRoot->left, node);
        }
    }

public:
    Node(Node &node){
        *left = *node.left;
        *rigth = *node.rigth;
        *parent = *node.parent;
        data = node.data;
        heigth = node.heigth;
    }

    Node() = default;


    /// Delete !!!
    void getInfo(){
        cout << "data: " << data << endl;
        cout << "heigth: " << heigth << endl;
        cout << "has leftChild: " << (left != nullptr) << endl;
        cout << "has rigthChild: " << (rigth != nullptr) << endl;
        cout << "has parent: " << (parent != nullptr) << endl;
    }

    explicit Node(T data){
        left = nullptr;
        rigth = nullptr;
        parent = nullptr;
        this->data = data;
        heigth = 1;
    }


    void deleteNode(Node<T>* node){
        if (node == nullptr)
            return;

        if (node->left != nullptr)
        {
            deleteNode(node->left);
            node->left = nullptr;
        }

        if (node->rigth != nullptr){
            deleteNode(node->rigth);
            rigth = nullptr;
        }
        delete node;
    }


    Node<T>& operator = (const Node<T>* node){
        data = node->data;
        heigth = node->heigth;

        if (node->left != nullptr){
            left = new Node<T>();
            *left = *node->left;
        }

        if (node->rigth != nullptr){
            rigth = new Node<T>();
            *rigth = *node->rigth;
        }
    }

    int operator == (Node<T>& node){
        return nodesIsTheSamePrivate(this,node);
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


    void addChild(T Data){
        addChildPrivate(Data, this);
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

    void addExistingChild(Node<T> *node){
        addExistingChildPrivate(this, node);
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


    T reducePrivate(T func(T value), Node<T>* node, int battery = 0) {
        if (node == nullptr)
            return 0;


        if (node->getLeftChild() != nullptr)
            battery = reducePrivate(func, node->getLeftChild(), battery);

        if (node->getRigthChild() != nullptr)
            battery = reducePrivate(func, node->getRigthChild(), battery);

        battery += func(node->getData());

        return battery;
    }

};

void func2(Node<int> *node){
    cout << node->getData() << endl;
}


template <class T>
class BinaryTree{
private:
    Node<T> * root = nullptr;

    Node<T>* findPrivate(const T &data, Node<T>* node) const {
        if (data == node->getData())
            return node;
        if (node->getRigthChild() != nullptr && node->getData() < data)
            return findPrivate(data, node->getRigthChild());

        if (node->getLeftChild() != nullptr && node->getData() < data)
            return findPrivate(data, node->getLeftChild());

        return nullptr;
    }

    void addTreeInArrayPrivate(Node<T>* node, myArraySequence<T>*array, int index){
        array->set(node->getData(), index);

        if (node->getLeftChild() != nullptr)
            addTreeInArrayPrivate(node->getLeftChild(), array, 2*index+1);
        else
            array->set(root->getData(),2*index+1);


        if (node->getRigthChild() != nullptr)
            addTreeInArrayPrivate(node->getRigthChild(), array, 2*index+2);
        else
            array->set(root->getData(),2*index+2);
    }

    BinaryTree* getSubTreePrivate(T value, Node<T>* node){
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
            return getSubTreePrivate(value, node->getRigthChild());

        if (value < node->getData())
            return getSubTreePrivate(value, node->getLeftChild());
    }

    int isSubTreePrivate(Node<T>* node, BinaryTree<T>* subTree){

        if (node == subTree->getRoot()) {
            return 1;
        }
        if (node->getLeftChild() != nullptr and node->getRigthChild() != nullptr){
            return isSubTreePrivate(node->getLeftChild(), subTree) || isSubTreePrivate(node->getRigthChild(), subTree);
        }

        if (node->getLeftChild() != nullptr)
            return isSubTreePrivate(node->getLeftChild(), subTree);

        if (node->getRigthChild() != nullptr)
            return isSubTreePrivate(node->getRigthChild(), subTree);

        return 0;
    }

    int getMaxHeigthPrivate(Node<T>* node){
        if (node == nullptr)
            return 0;

        int tempValue1 = -1;
        int tempValue2 = -1;

        if (node->getLeftChild() != nullptr){
            tempValue1 = getMaxHeigthPrivate(node->getLeftChild());
        }
        if (node->getRigthChild() != nullptr){
            tempValue2 = getMaxHeigthPrivate(node->getRigthChild());
        }


        if (node->getLeftChild() == nullptr and node->getRigthChild() == nullptr){
            return node->getHeigth();
        }


        if (tempValue1 > tempValue2)
            return tempValue1;
        else
            return tempValue2;
    }

    void deleteNodePrivate(T value, Node<T>* node){
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
            deleteNodePrivate(value, node->getLeftChild());

        if (value > node->getData() and node->getRigthChild() != nullptr)
            deleteNodePrivate(value, node->getRigthChild());
    }

    BinaryTree<T>* balancePrivate(Node<T>* node){
        if (isBalanced()){
            if (node == root)
                return this;
            auto *newTree = new BinaryTree<T>;
            *newTree = BinaryTree<T>(node);
            return newTree;
        }

        if (getMaxHeigthPrivate(node->getLeftChild()) > getMaxHeigthPrivate(node->getRigthChild())){
            Node<T>* lastRoot = node;
            Node<T>* newRootNode = node->getLeftChild();
            if (lastRoot != nullptr)
                newRootNode->addExistingChild(lastRoot);
            if (newRootNode->getLeftChild() != nullptr)
                newRootNode->addExistingChild(newRootNode->getLeftChild());
            if (newRootNode->getRigthChild() != nullptr)
                newRootNode->addExistingChild(newRootNode->getRigthChild());

            return balancePrivate(newRootNode);
        }
        if (getMaxHeigthPrivate(node->getLeftChild()) < getMaxHeigthPrivate(node->getRigthChild())){
            Node<T>* lastRoot = node;
            Node<T>* newRootNode = node->getRigthChild();
            if (lastRoot != nullptr)
                newRootNode->addExistingChild(lastRoot);
            if (newRootNode->getLeftChild() != nullptr)
                newRootNode->addExistingChild(newRootNode->getLeftChild());
            if (newRootNode->getRigthChild() != nullptr)
                newRootNode->addExistingChild(newRootNode->getRigthChild());

            return balancePrivate(newRootNode);
        }
    }

    void addNodeWithConditionPrivate( T func(T), Node<T>* node, Node<T>* newNode){
        if (node->getLeftChild() != nullptr && node->getData() == func(node->getLeftChild()->getData())){
            newNode->addExistingChild(node->getLeftChild());
            addNodeWithCondition(func, node->getLeftChild(), newNode);
        }

        if (node->getRigthChild() != nullptr && node->getData() == func(node->getRightChild()->getData())){
            newNode->addExistingChild(node->getRigthChild());
            addNodeWithCondition(func, node->getRigthChild(), newNode);
        }
    }

    void deleteNode2Private(T data, Node<T>* node){
        if (node == nullptr)
            return;

        if (node->getData() == data){
            delete node;
            node = nullptr;
        }

        if (data > node->getData()){
            if (node->getRigthChild() != nullptr)
                deleteNode2Private(data, node->getRigthChild());
        }

        if (data < node->getData()){
            if (node->getLeftChild() != nullptr)
                deleteNode2Private(data, node->getLeftChild());
        }
    }

public:

    BinaryTree( BinaryTree &tree){
        *root = *(tree.root);
    }

    explicit BinaryTree(Node<T> *node){
        root = new Node<T>;
        *root = *node;
        delete node;
    }

    explicit BinaryTree(T data){
        root = new Node<T>;
        *root = Node<T>(data);

    }

    BinaryTree() = default;

    ~BinaryTree(){
        delete root;
    }


    int operator == (BinaryTree<T>* tree){
        return root->nodesIsTheSame(root, tree->getRoot());
    }

    int operator != (BinaryTree<T>* tree){
        return not(root->nodesIsTheSame(root, tree->getRoot()));

    }

    BinaryTree<T>& operator = (const BinaryTree<T>* tree){
        if (root == nullptr)
            root = new Node<T>();
        *root = *(tree->root);
    }

    Node<T>* find(const T& data) const {
        return findPrivate(data, root);
    }

    int contain(const T &data) const{
        return find(data) != nullptr;
    }

    void addNode(T data) {
        if (root == nullptr) {
            root = new Node<T>(data);
            return;
        }
        root->addChild(data);
    }

    void deleteNode(T data){
        deleteNodePrivate(data, root);
    }

    void deleteNode2(T data){
       deleteNode2Private(data, root);

    }

    void addTreeInArray(myArraySequence<T>*array, int index){
        addTreeInArrayPrivate(root, array, index);
    }

    myArraySequence<T>* getArray(){
        myArraySequence<T>* array = new myArraySequence<int>;
        for (int i = 0; i < pow(2,getMaxHeigth(root) + 1); i++){array->append(0);}
        addInArray(array,0);
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

    BinaryTree<T>* getSubTree(T data){
        return getSubTreePrivate(data, root);
    }

    int isSubTree(BinaryTree<T>* subTree){
        return isSubTreePrivate(root, subTree);
    }

    int getMaxHeigth(){
        return getMaxHeigthPrivate(root);
    }

    int getMaxHeigthOfLeftChild(){
        if (root->getLeftChild() == nullptr){
            return 0;
        }
        return getMaxHeigthPrivate(root->getLeftChild());
    }

    int getMaxHeigthOfRigthChild(){
        if (root->getRigthChild() == nullptr){
            return 0;
        }
        return getMaxHeigthPrivate(root->geRigthChild());
    }

    void printTree(){
        KLPtraversal(&func2, root);
    }

    void printTree3(std::ostream& output = std::cout){
        if (root == nullptr)
            return;

        myArraySequence<T> array;
        for (int i = 0; i < pow(2,getMaxHeigth() + 1); i++){array.append(root->getData());}
        addTreeInArray(&array,0);
        int len = array.getLength();

        int i = 0;
        int k = 1;
        while(i < pow(2,getMaxHeigth()+1) - 1) {
            for (int j = 0; j < getMaxHeigth() * 4 - k; ++j) {cout<<" ";}
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
        addNodeWithConditionPrivate(func, root, newNode);
    }


    T reduce(T func(T value), Node<T>* node, int battery = 0) {
        reducePrivate(func, node, battery);

        return battery;
    }

    int isBalanced(){
        /*
        if (root->getLeftChild() == nullptr)
            return 0;
        if (root->getRigthChild() == nullptr)
            return 0;
        */
        auto left = root->getLeftChild() == nullptr ? 0 : getMaxHeigthPrivate(root->getLeftChild());
        auto right = root->getRigthChild() == nullptr ? 0 : getMaxHeigthPrivate(root->getRigthChild());

        return abs(left - right) <= 1;
//        return abs(getMaxHeigthPrivate(root->getLeftChild()) - getMaxHeigthPrivate(root->getRigthChild())) <= 1;
    }

    BinaryTree<T>* balance(){
        return balancePrivate(root);
    }
};


#endif //LAB3_MYBINARYTREE_H


