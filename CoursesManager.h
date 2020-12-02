//
// Created by basil on 12/1/2020.
//

#ifndef HW1_COURSESMANAGER_H
#define HW1_COURSESMANAGER_H
#include <iostream>
#include "list.h"
#include "library.h"
#include "classLecture.h"
#include "AVLtree.h"
#include <stdlib.h>
#include <time.h>
#include <exception>
#define ZERO 0
#define DONTCARE -1

template <class T>
class CoursesManager{
    public:
    AVLTree<int, classLecture<Node<AVLTree<T, AVLTree<T, T>>>>**> *courses_tree;
    List<AVLTree<T, AVLTree<T, T>>> *sorted_list;
    CoursesManager();
    ~CoursesManager();
    StatusType AddCourse(void *DS, int courseID, int numOfClasses);
};

template<class T>
CoursesManager<T>::~CoursesManager()
{
    delete this->courses_tree;
    delete this->sorted_list;
}

template<class T>
CoursesManager<T>::CoursesManager()
{
     this->courses_tree = new AVLTree<T, classLecture<Node<AVLTree<T, AVLTree<T, T>>>>**>() *courses_tree;
     this->sorted_list = new List<AVLTree<T, AVLTree<T, T>>>();
}

template<class T>
StatusType CoursesManager<T>::AddCourse(void *DS, int courseID, int numOfClasses)
{
    // if allocation error return ERROR_ALLOCATION
    try
    {
        treeNode<T, classLecture<Node<AVLTree<T, AVLTree<T, T>>>>**> *new_course = new treeNode<T, classLecture<Node<AVLTree<T, AVLTree<T, T>>>>**>();
        if(courseID<=0 || numOfClasses<=0 || DS==NULL )
        {
            return INVALID_INPUT;
        }

        //if exist return FAILURE;
        if(this->courses_tree->searchKey(courseID))
        {
            return FAILURE;
        }
        new_course->Id=&courseID;
        if( this->sorted_list->ifTimeAlReadyExists(ZERO) != nullptr)
        {
            new_course->Node_data = new linkedNode<AVLTree<AVLTree<int>>>*[numOfClasses];
            for(int i=0;i<numOfClasses ;i++)
                new_course->Node_data[i] = sorted_list->ifTimeAlReadyExists(ZERO);

            AVLNode<AVLTree<int>> *current = new AVLNode<AVLTree<int>>(courseID, nullptr);
            sorted_list->ifTimeAlReadyExists(ZERO)->data->addNode( current );
            current->Node_data = new AVLTree<int>();

            for(int i=0;i<numOfClasses ;i++)
            {
                int dont_care = DONTCARE;
                AVLNode<int> *c_i = new AVLNode<int>(i,&dont_care);
                current->Node_data->addNode(c_i);
            }
            this->courses_tree->addNode(new_course);
            return SUCCESS;
        } else{
            //add zero node to linkedlist
            new_course->Node_data = new linkedNode<AVLTree<AVLTree<int>>>*[numOfClasses];
            this->sorted_list->addNewNode(0);
            for(int i=0;i<numOfClasses ;i++)
                new_course->getData()[i] = sorted_list->ifTimeAlReadyExists(ZERO);
            AVLNode<AVLTree<int>> *current = new AVLNode<AVLTree<int>>(courseID, nullptr);
            sorted_list->ifTimeAlReadyExists(ZERO)->data->addNode( current );
            current->Node_data = new AVLTree<int>();
            //add class to linked list tree
            for(int i=0;i<numOfClasses ;i++)
            {
                int dont_care = DONTCARE;
                AVLNode<int> *c_i = new AVLNode<int>(i,&dont_care);
                current->Node_data->addNode(c_i);
            }
            this->courses_tree->addNode(new_course);
            return SUCCESS;
        }
    }
    catch (exception& e)
    {
        return ALLOCATION_ERROR;
    }
}


#endif //HW1_COURSESMANAGER_H
