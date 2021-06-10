////
//// Created by Pascal on 02.06.2021.
////
//
//#ifndef LAB3_MENU_H
//#define LAB3_MENU_H
//
//#include "myBinaryTree.h"
//
//int getNumberInRange(int down, int up){
//    while(true){
//        int number;
//        cin >> number;
//        if (down <= number <= up)
//            return number;
//    }
//}
//
//int randomInt() {
//    return rand()%1000;
//}
//
//float randomFloat() {
//    return (float)randomInt() + (float)randomInt()/(float)randomInt();
//}
//
//int getType() {
//    cout << "Choose data type\n"
//         << "\t1: int\n"
//         << "\t2: float\n";
//    return getNumberInRange(1, 2);
//}
//
//template <class T>
//T multIn(T value, T ratio){
//    return value * ratio;
//}
//
//template <class T>
//T doSquare(T value){
//    return value * value;
//}
//
//template <class T>
//T sum(T value, T ratio){
//    return value + ratio;
//}
//
//template <class T>
//T sub(T value, T ratio){
//    return value - ratio;
//}
//
//
//
//
//void createTree(myArraySequence<BinaryTree<int>*> *intTrees,
//                myArraySequence<BinaryTree<float>*> *floatTrees);
//
//void menu(){
//    myArraySequence<BinaryTree<int>*>intTrees;
//    myArraySequence<BinaryTree<float>*>floatTrees;
//    int number;
//    while(true) {
//        cout << "\t1: Make a tree\n"
//             << "\t2: Execute an operation with tree\n"
//             << "\t3: Print tree\n"
//             << "\t4: Delete tree\n"
//             << "\t5: Launch tree test\n"
//             << "\t6: quit\n"
//             << "Enter ";
//        number = getNumberInRange(1,6)
//
//        if (number == 6)
//            return;
//
//        switch (number) {
//            case 1:createTree(&intTrees, &floatTrees); break;
//            case 2: operationWithBinaryTree(&arrInt, &arrFloat); break;
//            default: break;
//        }
//    }
//
//    for (auto &i : arrInt) {
//        delete i;
//    }
//
//    for (auto &i : arrFloat) {
//        delete i;
//    }
//}
//
//template<class T>
//void createTreeManually(myArraySequence<BinaryTree<T>*> *arr){
//    int number;
//    cout << "To cancel - enter 0\n"
//            "To go on - enter 1\n";
//    number = getNumberInRange(0,1);
//    if (number == 0)
//        return;
//    cout << "Enter root number\n";
//    cin >> number;
//    auto node = new Node<T>(number);
//
//    int number2;
//    while(true) {
//        cout << "To finish enter " << number << endl;
//        cout << "Enter number to add" << endl;
//        cin >> number2;
//        if (number2 == number)
//            return;
//        node->addChild(number2);
//    }
//    auto Tree = new BinaryTree<T>(node);
//    arr->append(Tree);
//}
//
//template<class T>
//void createTreeAutomatically(myArraySequence<BinaryTree<T>*> *arr, T func()){
//    auto node = new Node<T>(func());
//    int length = getRandomLength();
//    for (int i = 1; i < length; i++){
//        node->addChild(func());
//    }
//    auto Tree = new BinaryTree<T>(node);
//    arr->append(Tree);
//}
//
//
//
//
//void createTree(myArraySequence<BinaryTree<int>*> *intTrees,
//                myArraySequence<BinaryTree<float>*> *floatTrees){
//    cout << "To create tree manually - enter 1\n"
//            "To create automatically - enter 2\n"
//            "To cancel - enter 0\n";
//    int number;
//    number = getNumberInRange(0,2);
//    if (number == 0)
//        return;
//
//    if (number== 1)
//        number = getType();
//        switch(number){
//            case 1:
//                createTreeManually(intTrees);break;
//            case 2:
//                createTreeManually(floatTrees);break;
//            default:break;}
//
//        if (number == 2){
//            switch (number) {
//                case 1:
//                    createTreeAutomatically(intTrees, randomInt);break;
//                case 2:
//                    createTreeAutomatically(floatTrees, randomFloat);break;
//                default:break;
//            }
//        }
//}
//
//template <class T>
//void printTrees(myArraySequence<BinaryTree<T>*> *arr){
//
//    cout << "You have " << arr->getLength() << " trees\n";
//    for (int i = 0; i < arr->getLength(); i++){
//        cout << "Tree with index " << i << " which has " << arr->get(i)->getNumberOfNodes() << " nodes\n";
//    }
//}
//
//template <class T>
//void mapOperation(myArraySequence<BinaryTree<T>*> *arr){
//    if (arr->getLength() == 0){
//        cout << "There is no trees with this type\n";
//        cout << "Automatic exit\n";
//        return;
//    }
//
//    printTrees(arr);
//    cout << "Enter index";
//    int index = getNumberInRange(0, arr->getLength());
//
//    cout << "To increase all elements of tree in number - enter 1\n"
//            "To square - enter 2\n"
//            "To sum or sub - enter 3\n";
//    int number;
//    number = getNumberInRange(1,3);
//    if (number == 1){
//        cout << "Enter number you want to multiply on tree";
//        int ratio;
//        cin >> ratio;
//        arr->get(index)->map(multIn(ratio));
//
//
//    }
//}
//
//template <class T>
//void operationWithBinaryTree(myArraySequence<BinaryTree<T>*> *arr){
//    int number;
//    cout << "To map - enter 1\n"
//            "To reduce - enter 2\n"
//            "To where - enter 3\n"
//            "To exit - enter 4\n";
//    number = getNumberInRange(1,4);
//}
//
//
//
//
//
//#endif //LAB3_MENU_H
