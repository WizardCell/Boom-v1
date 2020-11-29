//
// Created by basil on 11/29/2020.
//

#include "AVL_Tree.h"

template<class Data_type>
treeNode<Data_type>::~treeNode()
{
    delete Id;
    delete Node_data;
}

template<class Data_type>
Data_type *treeNode<Data_type>::getData()
{
    return Node_data;
}

template<class Data_type>
int treeNode<Data_type>::getBalanceFactor()
{
    return this->Balance_factor;
}

template<class Data_type>
void treeNode<Data_type>::ChangeHeight()
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
void treeNode<Data_type>::ChangeBalanceFactor()
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
void treeNode<Data_type>::RollLL()
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
    treeNode* temp=this->Left;
    this->LeftSon=temp->Right;
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
void treeNode<Data_type>::Roll()
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
void treeNode<Data_type>::RollRR()
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
    treeNode* temp=this->Right;
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
void treeNode<Data_type>::RollRL()
{
    this->Right->RollLL();
    RollRR();
}

template<class Data_type>
void treeNode<Data_type>::RollLR()
{
    this->Left->RollRR();
    RollLL();
}

template<class Data_type>
treeNode<Data_type>::treeNode(): Previous(nullptr), Left(nullptr), Right(nullptr), Id(nullptr)
, Node_data(nullptr), Balance_factor(0), Height(0){}

template<class Data_type>
treeNode<Data_type>::treeNode(const int &key, Data_type *data, treeNode *left_son, treeNode *right_son, int bf,
                              int height):Previous(nullptr), Left(left_son), Right(right_son), Id(new int(key))
                              , Node_data(data), Balance_factor(bf), Height(height){}

template<class Data_type>
treeNode<Data_type>::treeNode(const int &key, const Data_type &data, treeNode *left_son, treeNode *right_son, int bf,
                              int height) :Previous(nullptr), Left(left_son), Right(right_son), Id(new int(key))
                              , Node_data(new Data_type(data)), Balance_factor(bf), Height(height){}

template<class Data_type>
treeNode<Data_type>::treeNode(const treeNode &Copy) :
        Previous(Copy.Father), Left(Copy.LeftSon), Right(Copy.RightSon),
        Id(Copy.Key), Node_data(Copy.Node_data), Balance_factor(Copy.BF), Height(Copy.Height){}



