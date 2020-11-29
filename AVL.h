//
// Created by basil on 11/29/2020.
//

#ifndef AVL_TREE_AVL_H
#define AVL_TREE_AVL_H
#include "AVL_Tree.h"
using namespace std;

template<class Data_type>
class AVLTree {
    treeNode<Data_type> *tree_root;
    int nodes_number;
    //add non-related-functions
    //add not-related-classes(exceptions)
    //add non-related-template(void*)
public:
    AVLTree();
    void DeleteSubtree(treeNode<Data_type>* sub_root);
    ~AVLTree();
    treeNode<Data_type>* getRoot();
    int getNodesNumber();
    bool searchId(const int& id);
    void balanceTreeAfterChange(treeNode<Data_type>* node);
    void addNode(treeNode<Data_type>* node_Pointer);
    void removeNodeFromThisTree(treeNode<Data_type>* to_delete);
    treeNode<Data_type>* getNodeId(const int& id);
};

#endif //AVL_TREE_AVL_H
