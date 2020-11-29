#include <iostream>
#include "AVL.h"

void inorder(treeNode<int> *p) {
    if (p == NULL)
        return;
    inorder(p->Left);
    cout << *(p->Id) << " ";
    inorder(p->Right);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    AVLTree<int> y;
    //auto *a = new treeNode<int>(1,11);
    //(y).addNode(a);
//    auto *b = new treeNode<int>(2,11);
//    (*y).addNode(b);
//    auto *c = new treeNode<int>(3,11);
//    (*y).addNode(c);
//    auto *dd = new treeNode<int>(4,11);
//    (*y).addNode(dd);
//    auto *e = new treeNode<int>(5,11);
//    (*y).addNode(e);
//    inorder((*y).getRoot());
    return 0;
}