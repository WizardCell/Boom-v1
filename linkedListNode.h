//
// Created by basil on 11/30/2020.
//

#ifndef HW1_LINKEDLISTNODE_H
#define HW1_LINKEDLISTNODE_H

#include "AVLtree.h"
template <class data_type>
class linkedNode{
public:
    data_type* data;
    int node_time;
    linkedNode* next;
    linkedNode* previous;
    linkedNode<data_type>(int time_ini);
    ~linkedNode();
};

template <class data_type>
linkedNode<data_type>::linkedNode(int time_ini) :node_time(time_ini)
        {
            this->next= nullptr;
            this->previous= nullptr;
            this->data= nullptr;
        }

template <class data_type>
linkedNode<data_type>::~linkedNode()
{
    delete data;
}

#endif //HW1_LINKEDLISTNODE_H
