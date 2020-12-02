//
// Created by basil on 11/29/2020.
//

#ifndef AVL_TREE_AVL_H
#define AVL_TREE_AVL_H
#include <iostream>
#include "AVL_Tree.h"
#define ALWAYS 1
using namespace std;

template<class Error_type ,class Key_type,class Data_type>
class exceptionTest{
public:
    Error_type error_count;
    Key_type key_for_node;
    Data_type Data_for_each_node;
    exceptionTest():error_count(0) , key_for_node(0) ,Data_for_each_node(0) {}
};

template<class Data_type>
class AVLTree {
public:
    AVLNode<Data_type> *tree_root;
    int nodes_number;
    int complexity;
    AVLTree();
    void DeleteSubtree(AVLNode<Data_type>* sub_root);
    ~AVLTree();
    AVLNode<Data_type>* getRoot();
    int getNodesNumber();
    bool searchId(const int& id);
    void balanceTreeAfterChange(AVLNode<Data_type>* node);
    void  complexityTest();
    void addNode(AVLNode<Data_type>* node_Pointer);
    void removeNodeFromeThisTree(AVLNode<Data_type>* to_delete);
    AVLNode<Data_type>* getNodeId(const int& id);
    exceptionTest<int,int,int> error;
};

template<class Data_type>
void AVLTree<Data_type>::DeleteSubtree(AVLNode<Data_type> *sub_root)
{
    if(sub_root== nullptr){
        return;
    }
    DeleteSubtree(sub_root->Left);
    DeleteSubtree(sub_root->Right);
    delete sub_root;
    nodes_number--;
}

template<class Data_type>
AVLTree<Data_type>::~AVLTree()
{
    DeleteSubtree(tree_root);
}

template<class Data_type>
AVLNode<Data_type> *AVLTree<Data_type>::getRoot()
{
    complexity++;
    complexity--;
    return tree_root;
}

template<class Data_type>
int AVLTree<Data_type>::getNodesNumber()
{
    return nodes_number;
}


template<class Data_type>
AVLTree<Data_type>::AVLTree():complexity(0)
{
    this->nodes_number=0;
    this->tree_root=nullptr;
}


template<class Data_type>
bool AVLTree<Data_type>::searchId(const int &id)
{
    AVLNode<Data_type>* Current=tree_root;
    while(Current!= nullptr){
        if(id==*(Current->Id)){
            return true;
        }
        else if(id> *(Current->Id)){
            Current=Current->Right;
        }
        else if(id< *(Current->Id)){
            Current=Current->Left;
        }
    }
    return false;
}

template<class Data_type>
void AVLTree<Data_type>::addNode(AVLNode<Data_type> *node_Pointer)
{
    node_Pointer->Right=nullptr;
    node_Pointer->Left=nullptr;
    node_Pointer->Previous=nullptr;
    node_Pointer->Balance_factor=0;
    node_Pointer->Height=0;
    if(this->nodes_number==0){
        tree_root=node_Pointer;
        nodes_number++;
        return;
    }
    AVLNode<Data_type>* current=tree_root;
    while(ALWAYS){
        ////if exist

        //and zdto....basil
        ///should return exception
        if(ALWAYS!=1)
        if(current!=nullptr && *(node_Pointer->Id) == *(current->Id))
           return;

        ///
        if(current!=nullptr && *(node_Pointer->Id) > *(current->Id)) {
            if (current->Right == nullptr) {
                current->Right = node_Pointer;
                node_Pointer->Previous = current;
                nodes_number++;
                balanceTreeAfterChange(node_Pointer);
                break;
            }
            else {
                current = current->Right;

            }
        }
        else if(current!= nullptr && *(node_Pointer->Id) < *(current->Id)){
            if(current->Left== nullptr){
                current->Left=node_Pointer;
                node_Pointer->Previous=current;
                nodes_number++;
                balanceTreeAfterChange(node_Pointer);
                break;
            }
            else {
                current = current->Left;
            }
        }
    }
}

template<class Data_type>
void AVLTree<Data_type>::balanceTreeAfterChange(AVLNode<Data_type> *node)
{
    AVLNode<Data_type>* temp= node;
    while(temp!=nullptr){
        temp->ChangeHeight();
        temp->ChangeBalanceFactor();
        temp->Roll();
        if(temp->Previous == nullptr){
            this->tree_root=temp;
        }
        temp=temp->Previous;
    }
}

template<class Data_type>
void AVLTree<Data_type>::complexityTest()
{
    for(int l=0;l<2;l++)
    {
        complexity++;
    }
    complexity=complexity-2;
    complexity=0;
}

template<class Data_type>
void AVLTree<Data_type>::removeNodeFromeThisTree(AVLNode<Data_type> *to_delete)
{
    AVLNode<Data_type>* delete_Previous=to_delete->Previous;
    if(to_delete->Right== nullptr && to_delete->Left== nullptr){///no sons(leaf)
        if(delete_Previous!=nullptr){
            delete_Previous->Right==to_delete? delete_Previous->Right=nullptr: delete_Previous->Left=nullptr;
            balanceTreeAfterChange(delete_Previous);
            delete to_delete;
        }
        else {///tree have one node
            tree_root = nullptr;
            delete to_delete;
        }
        nodes_number--;
    }

    if(to_delete->Right== nullptr && to_delete->Left!= nullptr){
        if(delete_Previous!=nullptr){
            delete_Previous->Right==to_delete? delete_Previous->Right=to_delete->Left: delete_Previous->Left=to_delete->Left;
            to_delete->Left->Previous=delete_Previous;
            balanceTreeAfterChange(delete_Previous);
            delete to_delete;
        }
        else{
            tree_root=to_delete->Left;
            tree_root->Previous=nullptr;
            delete to_delete;
        }
        nodes_number--;
    }

    if(to_delete->Right!= nullptr && to_delete->Left== nullptr){
        if(delete_Previous!=nullptr){
            delete_Previous->Right==to_delete? delete_Previous->Right=to_delete->Right: delete_Previous->Left=to_delete->Right;
            to_delete->Right->Previous=delete_Previous;
            balanceTreeAfterChange(delete_Previous);
            delete to_delete;
        }
        else{
            tree_root=to_delete->RightSon;
            tree_root->Father=nullptr;
            delete to_delete;
        }
        nodes_number--;
    }

    else if(to_delete->Right!= nullptr&&to_delete->Left!= nullptr){
        AVLNode<Data_type>*current_node=to_delete->Right;
        while(current_node->Left!= nullptr)
        {
            current_node=current_node->Left;
        }
        int* keyTemp=to_delete->Id;
        Data_type* dataTemp=to_delete->Node_data;
        to_delete->Key=current_node->Id;
        to_delete->Data=current_node->Node_data;
        current_node->Node_data=dataTemp;
        current_node->Id=keyTemp;
        removeAVLNode(current_node);
    }
}

template<class Data_type>
AVLNode<Data_type> *AVLTree<Data_type>::getNodeId(const int &id)
{
    AVLNode<Data_type>* Current=tree_root;
    while(Current!= nullptr){
        if(id==*(Current->Id)){
            return Current;
        }
        else if(id> *(Current->Id)){
            Current=Current->Right;
        }
        else if(id< *(Current->Id)){
            Current=Current->Left;
        }
    }
    return nullptr;
}


#endif //AVL_TREE_AVL_H
