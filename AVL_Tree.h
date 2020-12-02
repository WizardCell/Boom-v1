//
// Created by basil on 11/29/2020.
//

#ifndef AVL_TREE_AVL_TREE_H
#define AVL_TREE_AVL_TREE_H
#include <iostream>
using namespace std;

template<class Data_type>
class AVLNode {

public:
    int *Id;
    Data_type *Node_data;
    int Height;
    int Balance_factor;
    AVLNode<Data_type> *Previous;
    AVLNode<Data_type> *Left;
    AVLNode<Data_type> *Right;
    AVLNode();
    // fix memory leak if there is.
   // AVLNode(const int& key, Data_type* data, AVLNode* left_son= nullptr, AVLNode* right_son= nullptr, int bf=0, int height=0);
    AVLNode( int& key,  Data_type* data, AVLNode* left_son= nullptr, AVLNode* right_son= nullptr, int bf=0, int height=0);
    //AVLNode(const AVLNode& Copy);
    ~AVLNode();
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


template<class Data_type>
AVLNode<Data_type>::~AVLNode()
{
    delete Id;
    delete Node_data;
}

template<class Data_type>
Data_type *AVLNode<Data_type>::getData()
{
    return Node_data;
}

template<class Data_type>
int AVLNode<Data_type>::getBalanceFactor()
{
    return this->Balance_factor;
}

template<class Data_type>
void AVLNode<Data_type>::ChangeHeight()
{
    if(Left== nullptr&&Right== nullptr){ ///leaf
        Height=0;
    }
    else if(Left== nullptr){
        Height=Right->Height+1;
    }
    else if(Right== nullptr){
        Height=Left->Height+1;
    }
    else if(Left->Height>Right->Height){
        Height=Left->Height+1;
    }
    else if(Right->Height>=Left->Height){
        Height=Right->Height+1;
    }
}

template<class Data_type>
void AVLNode<Data_type>::ChangeBalanceFactor()
{
    int Left_Height=0;
    int Right_Height=0;
    if(Left!= nullptr)
    {
        Left_Height=1+Left->Height;
    }
    if(Right!= nullptr)
    {
        Right_Height=1+Right->Height;
    }
    Balance_factor=(Left_Height-Right_Height);
}

template<class Data_type>
void AVLNode<Data_type>::RollLL()
{
    ///to be reviewed "need IFs"
    int position=0;
    if(this->Previous!= nullptr){
        if(this->Previous->Left==this)
        {
            position=-1;
        }
        else{
            position=1;
        }
    }
    AVLNode* temp=this->Left;
    this->Left=temp->Right;
    temp->Right=this;
    temp->Previous=this->Previous;

    if(this->Left!=nullptr)
    {
        this->Left->Previous=this;
    }

    if(position==1)
    {
        this->Previous->Right=temp;
    }
    if(position==-1)
    {
        this->Previous->Left=temp;
    }

    this->Previous=temp;

    this->ChangeHeight();
    this->ChangeBalanceFactor();
}

template<class Data_type>
void AVLNode<Data_type>::Roll()
{
    ///
    if(Balance_factor==2 && Left->Balance_factor>=0)
    {
        RollLL();
        return;
    }
    if(Balance_factor==2 && Left->Balance_factor==-1)
    {
        RollLR();
        return;
    }
    ///
    ///
    if(Balance_factor==-2)
    {
        if(Right->Balance_factor<=0)
        {
            RollRR();
            return;
        }
        else if(Right->Balance_factor==1)
        {
            RollRL();
            return;
        }
    }
    ///
}

template<class Data_type>
void AVLNode<Data_type>::RollRR()
{
    int position=0;
    if(this->Previous!= nullptr){
        if(this->Previous->Left==this){
            position=-1;
        }
        else{
            position=1;
        }
    }
    AVLNode* temp=this->Right;
    this->Right=temp->Left;
    if(this->Right!=nullptr){
        this->Right->Previous=this;
    }
    temp->Left=this;
    temp->Previous=this->Previous;

    if(position==1)
    {
        this->Previous->Right=temp;
    }
    if(position==-1)
    {
        this->Previous->Left=temp;
    }
    this->Previous=temp;

    this->ChangeHeight();
    this->ChangeBalanceFactor();
}

template<class Data_type>
void AVLNode<Data_type>::RollRL()
{
    this->Right->RollLL();
    RollRR();
}

template<class Data_type>
void AVLNode<Data_type>::RollLR()
{
    this->Left->RollRR();
    RollLL();
}

template<class Data_type>
AVLNode<Data_type>::AVLNode()
        {
            this->Previous = nullptr;
            this->Left = nullptr;
            this->Right = nullptr;
            this->Id = nullptr;
            this->Node_data = nullptr;
            this->Balance_factor =0;
            this->Height=0;
        }

//template<class Data_type>
//AVLNode<Data_type>::AVLNode(const int &key, Data_type *data, AVLNode *left_son, AVLNode *right_son, int bf,
//                              int height)
//{
//    this->Previous=nullptr;
//    this->Id=new int(key);
//    this->Left=left_son;
//    this->Right = right_son;
//    this->Node_data=data;
//    this->Balance_factor =bf;
//    this->Height=height;
//}

template<class Data_type>
AVLNode<Data_type>::AVLNode( int &key, Data_type *data, AVLNode *left_son, AVLNode *right_son, int bf,
                              int height)
{
    this->Previous=nullptr;
    this->Id=new int(key);
    this->Left=left_son;
    this->Right = right_son;
    this->Node_data=data;
    this->Balance_factor =bf;
    this->Height=height;
}

//template<class Data_type>
//AVLNode<Data_type>::AVLNode(const AVLNode &Copy) :
//        Previous(Copy.Father), Left(Copy.LeftSon), Right(Copy.RightSon),
//        Id(Copy.Key), Node_data(Copy.Node_data), Balance_factor(Copy.BF), Height(Copy.Height){}

#endif //AVL_TREE_AVL_TREE_H
