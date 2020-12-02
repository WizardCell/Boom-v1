//
// Created by basil on 12/1/2020.
//

#ifndef HW1_COURSESMANAGER_H
#define HW1_COURSESMANAGER_H
#include <iostream>
#include "linkedList.h"
#include "library.h"
#include "classLecture.h"
#include "AVLtree.h"
#include <stdlib.h>
#include <time.h>
#include <exception>
#define ZERO 0
#define DONTCARE -1

class CoursesManager{
    public:
    AVLTree<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>> *courses_tree;
    LinkedList<AVLTree<int, AVLTree<int, int>>> *sorted_list;
    CoursesManager();
    ~CoursesManager();
    StatusType AddCourse(void *DS, int courseID, int numOfClasses);
};

CoursesManager::~CoursesManager()
{
    delete this->courses_tree;
    delete this->sorted_list;
}

CoursesManager::CoursesManager()
{
     this->courses_tree = new AVLTree<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>>();
     this->sorted_list = new LinkedList<AVLTree<int, AVLTree<int, int>>>();
}


StatusType CoursesManager::AddCourse(void *DS, int courseID, int numOfClasses)
{
    // if allocation error return ERROR_ALLOCATION
    try
    {
        treeNode<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>> *new_course = new treeNode<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>>();
        new_course->is_array= true;
        if(courseID<=0 || numOfClasses<=0 || DS==NULL )
        {
            return INVALID_INPUT;
        }

        //if exist return FAILURE;
        if(this->courses_tree->searchKey(courseID))
        {
            return FAILURE;
        }
        int* course_id_new = new int(courseID);
        new_course->Key=course_id_new;
        if( this->sorted_list->ifTimeAlReadyExists(ZERO) != nullptr)
        {
            new_course-> Data = new classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>[numOfClasses];
            for(int i=0;i<numOfClasses ;i++)
            {
                new_course->Data[i].class_id = i;
                new_course->Data[i].class_time_node = sorted_list->ifTimeAlReadyExists(ZERO);
            }

            treeNode<int, AVLTree<int, int>> *current = new treeNode<int, AVLTree<int, int>>(courseID, nullptr);
            sorted_list->ifTimeAlReadyExists(ZERO)->data->addTreeNodeByPtr(current);
            current->Data = new AVLTree<int, int>();

            for(int i=0;i<numOfClasses ;i++)
            {
                int dont_care = DONTCARE;
                treeNode<int,int> *c_i = new treeNode<int,int>(i,dont_care);
                current->Data->addTreeNodeByPtr(c_i);
            }
            this->courses_tree->addTreeNodeByPtr(new_course);
            return SUCCESS;
        } else{
            //add zero node to linkedlist
            new_course-> Data = new classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>[numOfClasses];
            this->sorted_list->addNewNode(0);
            for(int i=0;i<numOfClasses ;i++)
            {
                new_course->Data[i].class_id = i;
                new_course->Data[i].class_time_node = sorted_list->ifTimeAlReadyExists(ZERO);
            }
            treeNode<int, AVLTree<int, int>> *current = new treeNode<int, AVLTree<int, int>>(courseID, nullptr);
            sorted_list->ifTimeAlReadyExists(ZERO)->data->addTreeNodeByPtr(current);
            current->Data = new AVLTree<int, int>();
            //add class to linked list tree
            for(int i=0;i<numOfClasses ;i++)
            {
                int dont_care = DONTCARE;
                treeNode<int,int> *c_i = new treeNode<int,int>(i,dont_care);
                current->Data->addTreeNodeByPtr(c_i);
            }
            this->courses_tree->addTreeNodeByPtr(new_course);
            return SUCCESS;
        }
    }
    catch (exception& e)
    {
        return ALLOCATION_ERROR;
    }
}


#endif //HW1_COURSESMANAGER_H
