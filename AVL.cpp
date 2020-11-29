//
// Created by basil on 11/29/2020.
//

#include "AVL.h"

template<class Data_type>
AVLTree<Data_type>::AVLTree():tree_root(nullptr), nodes_number(0){}

template<class Data_type>
void AVLTree<Data_type>::DeleteSubtree(treeNode<Data_type> *sub_root)
{
    if(sub_root== nullptr){
        return;
    }
    DestroySubtree(sub_root->Left);
    DestroySubtree(sub_root->Right);
    delete sub_root;
    nodes_number--;
}

template<class Data_type>
AVLTree<Data_type>::~AVLTree()
    {
        DeleteSubtree(tree_root);
    }

template<class Data_type>
treeNode<Data_type> *AVLTree<Data_type>::getRoot()
{
    return tree_root;
}

template<class Data_type>
int AVLTree<Data_type>::getNodesNumber()
{
    return nodes_number;
}

template<class Data_type>
bool AVLTree<Data_type>::searchId(const int &id)
{
    treeNode<Data_type>* Current=tree_root;
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
void AVLTree<Data_type>::addNode(treeNode<Data_type> *node_Pointer)
{
    node_Pointer->Right=nullptr;
    node_Pointer->Left=nullptr;
    node_Pointer->Previous=nullptr;
    node_Pointer->Balance_factor=0;
    node_Pointer->Height=0;
    if(nodes_number==0){
        tree_root=node_Pointer;
        nodes_number++;
        return;
    }
    treeNode<Data_type>* current=tree_root;
    while(1){
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
void AVLTree<Data_type>::balanceTreeAfterChange(treeNode<Data_type> *node) 
{
    treeNode<Data_type>* temp= node;
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
void AVLTree<Data_type>::removeNodeFromeThisTree(treeNode<Data_type> *to_delete) 
{
    treeNode<Data_type>* delete_Previous=to_delete->Previous;
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
        treeNode<Data_type>*current_node=to_delete->Right;
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
        removeTreeNode(current_node);
    }
}

template<class Data_type>
treeNode<Data_type> *AVLTree<Data_type>::getNodeId(const int &id)
{
    treeNode<Data_type>* Current=tree_root;
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


