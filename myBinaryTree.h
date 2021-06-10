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
    Node *right = nullptr;
    Node *parent = nullptr;
    T data = 0;
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
            node = new Node<T>(Tdata);
            return;
        }

        if (Tdata < node->data){
            if (node->left == nullptr){
                node->left = new Node<T>(Tdata);
                node->left->parent = node;
                node->left->heigth = node->heigth + 1;
                return;
            }
            else
                return addChildPrivate(Tdata, node->left);
        }
        if (Tdata > node->data){
            if (node->right == nullptr){
                node->right = new Node<T>(Tdata);
                node->right->parent = node;
                node->right->heigth = node->heigth + 1;
                return;
            }
            else
                return addChildPrivate(Tdata, node->right);
        }
    }

    void addExistingChildPrivate(Node<T> *newRoot , Node<T> *node){

        if (newRoot->getData() < node->getData()){
            if (newRoot->getRigthChild() == nullptr)
                newRoot->right = node;
            else
                addExistingChildPrivate(newRoot->right, node);
        }

        if (newRoot->getData() > node->getData()){
            if (newRoot->getLeftChild() == nullptr)
                newRoot->left = node;
            else
                addExistingChildPrivate(newRoot->left, node);
        }
    }


    Node<T>* RightRotation(Node *x)
    {
        Node *y=x->left;
        x->left=y->right;
        y->right=x;
        return y;
    }

    Node<T> *LeftRotation(Node *y)
    {
        Node *x=y->right;
        y->right=x->left;
        x->left=y;
        return x;
    }


    void deleteNodePrivate(Node<T>* node){
        if (node == nullptr)
            return;
        deleteNodePrivate(node->left);
        deleteNodePrivate(node->right);
        node->resetChildForParent();
        delete node;
    }

public:
    Node* Balance(){
        return BalancePrivate(this);
    }

    explicit Node(Node *node){
        *this = *node;
    }

    Node() = default;

    explicit Node(T data){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        this->data = data;
        heigth = 1;
    }

    void deleteNode(){
        deleteNodePrivate(this);
    }

    void resetChildForParent(){
        if (parent == nullptr)
            return;

        if (parent->left == this)
            parent->left = nullptr;

        if (parent->right == this)
            parent->right = nullptr;
    }

    Node<T>& operator = (const Node<T>& node){
        data = node.data;
        heigth = node.heigth;

        if (node.left != nullptr){
            left = new Node<T>(node.left);
        }

        if (node.right != nullptr){
            right = new Node<T>(node.right);
        }
        return *this;
    }

    int operator == (Node<T>& node){
        return nodesIsTheSamePrivate(this,node);
    }

    int operator != (Node<T>& node){
        return  !nodesIsTheSame(this,node);
    }

    int nodeIsTheSame(Node<T>* node){
        return nodesIsTheSamePrivate(this,node);
    }

    Node * getLeftChild(){
        return left;
    }

    Node * getRigthChild(){
        return right;
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
            case 2: right = newChild;
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

        return nullptr;
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
            root->deleteNode();
            root = nullptr;
            return;
        }

        if (node->getData() == value){
            node->resetChildForParent();
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

    void addNodeWithConditionPrivate( int func(T,T, int), Node<T>* node, Node<T>* newNode){
        if (node->getLeftChild() != nullptr && func(node->getData(), node->getLeftChild()->getData(), 1)){
            newNode->addExistingChild(node->getLeftChild());
            addNodeWithCondition(func, node->getLeftChild(), newNode);
        }

        if (node->getRigthChild() != nullptr && func(node->getData(), node->getRigthChild()->getData(), 2)){
            newNode->addExistingChild(node->getRigthChild());
            addNodeWithCondition(func, node->getRigthChild(), newNode);
        }
    }

    void mapPrivate(T func(T), Node<T>* node){
        if (root == nullptr)
            return;

        node->setValue(func(node->getData()));

        if (node->getLeftChild() != nullptr)
            mapPrivate(func, node->getLeftChild());

        if (node->getRigthChild() != nullptr)
            mapPrivate(func, node->getRigthChild());
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

    int getNumberOfNodesPrivate(Node<T>* node, int numbers = 0) {
        if (node == nullptr)
            return 0;

        numbers++;

        if (node->getLeftChild() == nullptr and node->getRigthChild() == nullptr)
            return numbers;

        if (node->getLeftChild() != nullptr and node->getRigthChild() != nullptr) {
            return getNumberOfNodesPrivate(node->getLeftChild(), numbers) +
                   getNumberOfNodesPrivate(node->getRigthChild(), numbers) - numbers;
        }

        if (node->getLeftChild() != nullptr) {
            return getNumberOfNodesPrivate(node->getLeftChild(), numbers);
        }

        if (node->getRigthChild() != nullptr) {
            return getNumberOfNodesPrivate(node->getRigthChild(), numbers);
        }

    }

public:

    BinaryTree(BinaryTree &tree){
        if (root == nullptr){
            root = new Node<T>(tree.getRoot());
        }
        *root = *tree.root;
    }

    explicit BinaryTree(Node<T> *node){
        root = node;
    }

    explicit BinaryTree(T data){
        root = new Node<T>(data);

    }

    BinaryTree() = default;

    ~BinaryTree(){
        delete root;
    }

    int operator == (BinaryTree<T>* tree){
        if (root == nullptr and tree == nullptr or root == nullptr and tree->getRoot() == nullptr)
            return 1;
        if (root == nullptr and tree != nullptr or root != nullptr and tree == nullptr)
            return 0;
        return root->nodesIsTheSame(root, tree->getRoot());
    }

    int operator != (BinaryTree<T>* tree){
        return root != tree->getRoot();

    }

    BinaryTree<T>& operator = (const BinaryTree<T>* tree){
        if (root == nullptr){
            root = new Node<T>(tree->getRoot());
            return *this;
        }
        *root = *(tree->root);
        return *this;
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


    void addTreeInArray(myArraySequence<T>*array, int index){
        addTreeInArrayPrivate(root, array, index);
    }

    myArraySequence<T>* getArray(){
        myArraySequence<T>* array = new myArraySequence<int>;
        for (int i = 0; i < pow(2,getMaxHeigth(root) + 1); i++){array->append(0);}
        addTreeInArrayPrivate(root, array,0);
        return array;
    }

    int getNumberOfNodes(){
        getNumberOfNodesPrivate(root, 0);
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

    void map(T func(T)){
        mapPrivate(func, root);
    }


    BinaryTree<T>* where(int func(T,T,int)){
        auto newRootNode = new Node<T>(root);
        auto newTree = new BinaryTree<T>(newRootNode);
        addNodeWithCondition(func, newTree);
        return newTree;

    }

    void addNodeWithCondition( int func(T,T),Node<T>* newNode){
        addNodeWithConditionPrivate(func, root, newNode);
    }


    T reduce(T func(T value), Node<T>* node, int battery = 0) {
        reducePrivate(func, node, battery);

        return battery;
    }

    int isBalanced(){
        auto left = root->getLeftChild() == nullptr ? 0 : getMaxHeigthPrivate(root->getLeftChild());
        auto right = root->getRigthChild() == nullptr ? 0 : getMaxHeigthPrivate(root->getRigthChild());

        return abs(left - right) <= 1;
    }

    BinaryTree<T>* balance(){
        return balancePrivate(root);
    }
};


#endif //LAB3_MYBINARYTREE_H


