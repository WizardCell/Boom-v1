//
// Created by basil on 11/30/2020.
//

#ifndef HW1_LINKEDLIST_H
#define HW1_LINKEDLIST_H
#define EMPTY_LIST 0
#include "linkedListNode.h"
template <class data_type>
class LinkedList {
public:
    int size_of_list;
    int complex_check;
    linkedNode<data_type> *head;
    linkedNode<data_type> *last;
    linkedNode<data_type> * ifTimeAlReadyExists(int node_time);
    LinkedList<data_type>();
    ~LinkedList<data_type>();
    int GetListSize();
    linkedNode<data_type>* addNewNode(int node_time);
    bool isEmpty();
    void removeNodeFromThis(linkedNode<data_type>* node_to_delete);
    linkedNode<data_type>* GetFirst();
    linkedNode<data_type>* GetLast();
};

template <class data_type>
LinkedList<data_type>::LinkedList():complex_check(0)
{

    linkedNode<data_type> *ini_node = new linkedNode<data_type>(0); //time zero
    this->head = ini_node;
    this->last=ini_node;
    this->size_of_list=1;
}

template<class data_type>
LinkedList<data_type>::~LinkedList<data_type>()
{
    linkedNode<data_type>* get_head = this->head;
    while(get_head){
        get_head = get_head->next;
        if(get_head == nullptr){
            delete this->last;
        }
        else if(get_head!= nullptr) delete get_head->previous;
    }
}

template<class data_type>
bool LinkedList<data_type>::isEmpty()
{
    if(this->head== nullptr)
        return true;
    return false;
}

template<class data_type>
int LinkedList<data_type>::GetListSize()
{
    return this->size_of_list;
}

template<class data_type>
linkedNode<data_type> *LinkedList<data_type>::addNewNode(int node_time)
{
    linkedNode<data_type> *add_this_node = new linkedNode<data_type>(node_time);
    if (this->isEmpty())
    {
        this->head = add_this_node;
        add_this_node->previous = nullptr;
        add_this_node->next = nullptr;
        add_this_node->node_time=node_time;
        this->last = add_this_node;
        this->size_of_list++;
        return add_this_node;
    }
    linkedNode<data_type> *ptr = this->head;
    while(ptr!= nullptr && ptr->node_time<node_time) {
        ptr = ptr -> next;
    }
    if(ptr== nullptr)
    {
        this->last->next=add_this_node;
        add_this_node->previous=this->last;
        this->last=ptr;
        add_this_node->next = nullptr;
        add_this_node->node_time=node_time;
        this->size_of_list++;
        return add_this_node;
    }
    ptr->previous->next=add_this_node;
    add_this_node->next=ptr;
    add_this_node->previous=ptr->previous;
    ptr->previous = add_this_node;
    add_this_node->node_time=node_time;
    this->size_of_list++;
    complex_check++;
    complex_check--;
    return add_this_node;
}

template<class data_type>
linkedNode<data_type> *LinkedList<data_type>::GetFirst()
{
    return this->head;
}

template<class data_type>
linkedNode<data_type> *LinkedList<data_type>::GetLast()
{
    return this->last;
}

template<class data_type>
void LinkedList<data_type>::removeNodeFromThis(linkedNode<data_type> *node_to_delete)
{
    if(node_to_delete== nullptr)
    {
        return;
    }
    if(node_to_delete->next== nullptr&&node_to_delete->previous== nullptr){
        this->last= nullptr;
        this->head= nullptr;
        delete node_to_delete;
        this->size_of_list= 0;
        return;
    }
    if(node_to_delete->previous== nullptr){
        node_to_delete->next->previous= nullptr;
        this->head=node_to_delete->next;
        delete node_to_delete;
        this->size_of_list--;
        return;
    }
    if(node_to_delete->next== nullptr){
        node_to_delete->previous->next= nullptr;
        this->last=node_to_delete->previous;
        delete node_to_delete;
        this->size_of_list--;
        return;
    } else{
        node_to_delete->next->previous=node_to_delete->previous;
        node_to_delete->previous->next=node_to_delete->next;
        delete node_to_delete;
        this->size_of_list--;
        return;
    }
}

template<class data_type>
linkedNode<data_type> *  LinkedList<data_type>::ifTimeAlReadyExists(int node_time)
{
    linkedNode<data_type> *p= this->head;
    while(p!= nullptr)
    {
        if(p->node_time == node_time)
            return p;
        p = p->next;
    }
    return nullptr;
}


#endif //HW1_LINKEDLIST_H
