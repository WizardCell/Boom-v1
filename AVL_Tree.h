//
// Created by basil on 11/29/2020.
//

#ifndef AVL_TREE_AVL_TREE_H
#define AVL_TREE_AVL_TREE_H
#include <iostream>
using namespace std;

template<class Data_type>
class treeNode {

public:
    int *Id;
    Data_type *Node_data;
    int Height;
    int Balance_factor;
    treeNode<Data_type> *Previous;
    treeNode<Data_type> *Left;
    treeNode<Data_type> *Right;
    treeNode();
    // prevent any memory leak.
    treeNode(const int& key, Data_type* data, treeNode* left_son= nullptr, treeNode* right_son= nullptr, int bf=0, int height=0);
    treeNode(const int& key, const Data_type& data, treeNode* left_son= nullptr, treeNode* right_son= nullptr, int bf=0, int height=0);
    treeNode(const treeNode& Copy);
    ~treeNode();
    Data_type* getData();
    int getBalanceFactor();
    void ChangeBalanceFactor();
    void ChangeHeight();
    void RollLL();
    void RollRR();
    void RollLR();
    void RollRL();
    void Roll();
};



#endif //AVL_TREE_AVL_TREE_H
