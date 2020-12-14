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
#include <exception>
#include <new>
#define ZERO 0
#define DONTCARE -1

class CoursesManager{
    public:

    AVLTree<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>> *courses_tree;
    LinkedList<AVLTree<int, AVLTree<int, int>>> *sorted_list;

    CoursesManager();
    ~CoursesManager();

    StatusType AddCourseManger(void *DS, int courseID, int numOfClasses);
    StatusType TimeViewedManger(void *DS, int courseID, int classID, int *timeViewed);
    StatusType RemoveCourseManger(void *DS, int courseID);
    StatusType WatchClassManger(void *DS, int courseID, int classID, int time);
    StatusType GetMostViewedClassesManger(void *DS, int numOfClasses, int *courses, int *classes);
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



treeNode<int,int>* sortedArrayToBST_aux(int start, int end)
{
    /* Base Case */
    if (start > end)
        return nullptr;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    int dont_care=-1;
    treeNode<int,int>* root = new treeNode<int,int>(mid,dont_care);

    /* Recursively construct the left subtree
    and make it left child of root */
    root->Left = sortedArrayToBST_aux( start,mid - 1);
    if( root->Left!= nullptr)
    root->Left->Up=root;
    /* Recursively construct the right subtree
    and make it right child of root */
    root->Right = sortedArrayToBST_aux(mid + 1, end);
    if(root->Right!= nullptr)
    root->Right->Up=root;
    return root;
}


StatusType CoursesManager::AddCourseManger(void *DS, int courseID, int numOfClasses)
{
    // if allocation error return ERROR_ALLOCATION
    try
    {
        if(courseID<=0 || numOfClasses<=0 || DS==NULL )
        {
            return INVALID_INPUT;
        }
        treeNode<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>> *new_course = new treeNode<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>>();
        new_course->is_array= true;
        //if exist return FAILURE;
        if(this->courses_tree->searchKey(courseID))
        {
            delete new_course;
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
                new_course->Data[i].constant_number_of_class=numOfClasses;
                new_course->Data[i].class_time_node = sorted_list->ifTimeAlReadyExists(ZERO);
            }

            treeNode<int, AVLTree<int, int>> *current = new treeNode<int, AVLTree<int, int>>(courseID, nullptr);
            sorted_list->ifTimeAlReadyExists(ZERO)->data->addthisTreeNodep(current);
            current->Data = new AVLTree<int, int>();

//            for(int i=0;i<numOfClasses ;i++)
//            {
//                int dont_care = DONTCARE;
//                treeNode<int,int> *c_i = new treeNode<int,int>(i,dont_care);
//                current->Data->addthisTreeNodep(c_i);
//            }
            current->Data->nodesAmount=numOfClasses;
            current->Data->Head=sortedArrayToBST_aux(0,numOfClasses-1);
            this->courses_tree->addthisTreeNodep(new_course);
            sorted_list->ifTimeAlReadyExists(ZERO)->data->min_number = sorted_list->ifTimeAlReadyExists(ZERO)->data->minValue();
            current->Data->min_number = current->Data->minValue();
            return SUCCESS;
        } else{
            //add zero node to linkedlist
            new_course-> Data = new classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>[numOfClasses];
            linkedNode<AVLTree<int,AVLTree<int,int>>> *zero_time_node_to_add = new linkedNode<AVLTree<int,AVLTree<int,int>>>(ZERO);
            //zero_time_node_to_add->data=new AVLTree<int,AVLTree<int,int>>();
            this->sorted_list->addNewNode(zero_time_node_to_add);
            //dont know why but it works
            //delete  zero_time_node_to_add->data;
            //
            for(int i=0;i<numOfClasses ;i++)
            {
                new_course->Data[i].class_id = i;
                new_course->Data[i].constant_number_of_class=numOfClasses;
                new_course->Data[i].class_time_node = sorted_list->ifTimeAlReadyExists(ZERO);
            }
            treeNode<int, AVLTree<int, int>> *current = new treeNode<int, AVLTree<int, int>>(courseID, nullptr);
            sorted_list->ifTimeAlReadyExists(ZERO)->data = new AVLTree<int, AVLTree<int, int>>();
            sorted_list->ifTimeAlReadyExists(ZERO)->data->addthisTreeNodep(current);
            current->Data = new AVLTree<int, int>();
            //add class to linked list tree
//            for(int i=0;i<numOfClasses ;i++)
//            {
//                int dont_care = DONTCARE;
//                treeNode<int,int> *c_i = new treeNode<int,int>(i,dont_care);
//                current->Data->addthisTreeNodep(c_i);
//            }
            current->Data->nodesAmount=numOfClasses;
            current->Data->Head=sortedArrayToBST_aux(0,numOfClasses-1);
            this->courses_tree->addthisTreeNodep(new_course);
            sorted_list->ifTimeAlReadyExists(ZERO)->data->min_number = sorted_list->ifTimeAlReadyExists(ZERO)->data->minValue();
            current->Data->min_number = current->Data->minValue();
            return SUCCESS;
        }
    }
    catch (std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType CoursesManager::TimeViewedManger(void *DS, int courseID, int classID, int *timeViewed)
{
    try {
        if(DS==NULL || courseID<=0 ||classID<0)
        {
            return INVALID_INPUT;
        }
        if( !((CoursesManager *)DS)->courses_tree->searchKey(courseID))
        {
            return FAILURE;
        }
       // int numOfClasses = sizeof(((CoursesManager *)DS)->courses_tree->getByKey(courseID)->Data)/sizeof(((CoursesManager *)DS)->courses_tree->getByKey(courseID)->Data[0]);
        int numOfClasses= ((CoursesManager *)DS)->courses_tree->getByKey(courseID)->Data->constant_number_of_class;
        if(numOfClasses<=classID)
            return INVALID_INPUT;
        *timeViewed = ((CoursesManager *)DS)->courses_tree->getByKey(courseID)->Data[classID].class_time_node->node_time;
        return SUCCESS;
    } catch (std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType CoursesManager::RemoveCourseManger(void *DS, int courseID)
{
        try {
        if(courseID<=0 || DS==NULL )
        {
            return INVALID_INPUT;
        }
        if( !((CoursesManager *)DS)->courses_tree->searchKey(courseID))
        {
            return FAILURE;
        }
        //remove --- adrbbbb
        treeNode<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>>* to_delete_course = ((CoursesManager *)DS)->courses_tree->getByKey(courseID);
        int numOfClasses = to_delete_course->Data->constant_number_of_class;
        for(int i=0 ; i < numOfClasses ; i++)
        {
            linkedNode<AVLTree<int, AVLTree<int, int>>> *time_node_i = to_delete_course->Data[i].class_time_node;
            if(time_node_i->data->getRoot() == nullptr)
                sorted_list->removeNodeFromThis(time_node_i);
            //find cousre node in time_node_i tree && remove classid from course tree
            time_node_i->data->getByKey(courseID)->Data->removeTreeNode(   time_node_i->data->getByKey(courseID)->Data->getByKey(i)  );
            //
            sorted_list->ifTimeAlReadyExists(time_node_i->node_time)->data->min_number = sorted_list->ifTimeAlReadyExists(time_node_i->node_time)->data->minValue();
            if(time_node_i->data->getByKey(courseID)->Data->getRoot()== nullptr)
                time_node_i->data->removeTreeNode( time_node_i->data->getByKey(courseID) );
            if(time_node_i->data->getRoot() == nullptr)
                sorted_list->removeNodeFromThis(time_node_i);
            ///////////
        }//end of for ->>> array of classses
        courses_tree->removeTreeNode(courses_tree->getByKey(courseID));
            //
        return SUCCESS;
    }catch (std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType CoursesManager::WatchClassManger(void *DS, int courseID, int classID, int time)
{
    try{
        if(  DS==NULL || courseID<=0 || classID<0 || time<=0)
            return INVALID_INPUT;
        if( !((CoursesManager *)DS)->courses_tree->searchKey(courseID))
        {
            return FAILURE;
        }
        int numOfClasses= ((CoursesManager *)DS)->courses_tree->getByKey(courseID)->Data->constant_number_of_class;
        if(numOfClasses < 1+ classID)
            return INVALID_INPUT;

        //add time --- adrbbbb

        treeNode<int, classLecture<linkedNode<AVLTree<int, AVLTree<int, int>>>>>* to_addTime_course = ((CoursesManager *)DS)->courses_tree->getByKey(courseID);
        linkedNode<AVLTree<int, AVLTree<int, int>>> *time_node = to_addTime_course->Data[classID].class_time_node;
        int new_time_toAdd = time +  time_node->node_time;
        to_addTime_course->Data[classID].class_id=new_time_toAdd;
        if(time_node->data->getRoot() == nullptr)
            sorted_list->removeNodeFromThis(time_node);
        //find cousre node in time_node_i tree && remove classid from course tree
        time_node->data->getByKey(courseID)->Data->removeTreeNode(   time_node->data->getByKey(courseID)->Data->getByKey(classID)  );
        //
        if(time_node->data->getByKey(courseID)->Data->getRoot()== nullptr)
            time_node->data->removeTreeNode( time_node->data->getByKey(courseID) );
        if(time_node->data->getRoot() == nullptr)
            sorted_list->removeNodeFromThis(time_node);
        ///make new node
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if( this->sorted_list->ifTimeAlReadyExists(new_time_toAdd) != nullptr)
        {
            //af7s ada akrs mwjod blnode ljded***** sle7!
            treeNode<int, AVLTree<int, int>> *current;
            AVLTree<int, AVLTree<int, int>> *tempA = sorted_list->ifTimeAlReadyExists(new_time_toAdd)->data;
            // //af7s ada akrs mwjod blnode ljded***** sle7!
            if(tempA->getByKey(courseID)== nullptr)
            {
                current = new treeNode<int, AVLTree<int, int>>(courseID, nullptr);
                tempA->addthisTreeNodep(current);
                current->Data = new AVLTree<int, int>();
            } else{
                current = tempA->getByKey(courseID);
            }
            //end check
                int dont_care = DONTCARE;
                treeNode<int,int> *c_i = new treeNode<int,int>(classID,dont_care);
                current->Data->addthisTreeNodep(c_i);
            to_addTime_course->Data[classID].class_time_node =  this->sorted_list->ifTimeAlReadyExists(new_time_toAdd);
            sorted_list->ifTimeAlReadyExists(new_time_toAdd)->data->min_number = sorted_list->ifTimeAlReadyExists(new_time_toAdd)->data->minValue();
            current->Data->min_number = current->Data->minValue();
            return SUCCESS;
        } else{
            //add time node to linkedlist
            linkedNode<AVLTree<int,AVLTree<int,int>>> *new_time_node_to_add = new linkedNode<AVLTree<int,AVLTree<int,int>>>(new_time_toAdd);
            new_time_node_to_add->data =  new AVLTree<int,AVLTree<int,int>>();
            this->sorted_list->addNewNode(new_time_node_to_add);
            treeNode<int, AVLTree<int, int>> *current = new treeNode<int, AVLTree<int, int>>(courseID, nullptr);
            // no need to create new data because addnew node make new data
            //sorted_list->ifTimeAlReadyExists(new_time_toAdd)->data = new AVLTree<int, AVLTree<int, int>>();
            sorted_list->ifTimeAlReadyExists(new_time_toAdd)->data->addthisTreeNodep(current);
            current->Data = new AVLTree<int, int>();
            //add class to linked list tree
                int dont_care = DONTCARE;
                treeNode<int,int> *c_i = new treeNode<int,int>(classID,dont_care);
                current->Data->addthisTreeNodep(c_i);
            to_addTime_course->Data[classID].class_time_node =  this->sorted_list->ifTimeAlReadyExists(new_time_toAdd);
            sorted_list->ifTimeAlReadyExists(new_time_toAdd)->data->min_number = sorted_list->ifTimeAlReadyExists(new_time_toAdd)->data->minValue();
            current->Data->min_number = current->Data->minValue();
            return SUCCESS;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //end of for ->>> array of classses
    }
    catch (std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
}


void getAllCourseClasses_aux(int numOfClasses, int *courses, int *classes , int& cnt ,treeNode<int,int> *right_tree , int course_num)
{
    if(right_tree== nullptr)
        return;

    getAllCourseClasses_aux(numOfClasses,courses,classes,cnt, right_tree->Left , course_num);
    if(numOfClasses<=cnt)
        return;
    courses[cnt] = course_num;
    classes[cnt] = *right_tree->Key;
    cnt++;
    getAllCourseClasses_aux(numOfClasses,courses,classes,cnt, right_tree->Right,course_num);
}


void getAllCourseClasses(int numOfClasses, int *courses, int *classes , int& cnt ,treeNode<int,AVLTree<int,int>> *current_course)
{
    //treeNode<int,int> *current_class = current_course->getData()->minValue();
    treeNode<int,int> *current_class = current_course->getData()->min_number;
    while(cnt<numOfClasses && current_class!= nullptr)
    {
        courses[cnt] = *current_course->Key;
        classes[cnt] = *current_class->Key;
        cnt++;
        treeNode<int,int> *current_class_parent = current_class;
        //go Rightssss
        current_class=current_class->Right;
        getAllCourseClasses_aux(numOfClasses,courses,classes,cnt,current_class,*current_course->Key);
        //
        //go up and repeat
        current_class = current_class_parent->Up;
    }
}


void auxCoursesInOrder(int numOfClasses, int *courses, int *classes , int& cnt ,treeNode<int,AVLTree<int,int>> *right_tree)
{
    if(right_tree== nullptr)
        return;

    auxCoursesInOrder(numOfClasses,courses,classes,cnt, right_tree->Left);
    if(numOfClasses<=cnt)
        return;
    //do
    getAllCourseClasses(numOfClasses,courses,classes , cnt , right_tree);
    //
    auxCoursesInOrder(numOfClasses,courses,classes,cnt, right_tree->Right);
}



StatusType CoursesManager::GetMostViewedClassesManger(void *DS, int numOfClasses, int *courses, int *classes)
{
    try{
        if(numOfClasses<=0 || DS==NULL)
        {
            return INVALID_INPUT;
        }
//        if(((CoursesManager *)DS)->courses_tree->getNodesAmount() < numOfClasses)
//        {
//            return FAILURE;
//        }
        //dooo it

        linkedNode<AVLTree<int,AVLTree<int,int>>> *current_list = this->sorted_list->GetLast();
        int cnt=0;
        //list
        while(cnt<numOfClasses)
        {
            //treeNode<int,AVLTree<int,int>> *current_course = current_list->data->minValue();
            treeNode<int,AVLTree<int,int>> *current_course = current_list->data->min_number;
            current_list = current_list->previous;
            //course
            while(cnt<numOfClasses && current_course!= nullptr)
            {
               //get m or less than m classes from this course
               //while
               // class
               getAllCourseClasses(numOfClasses,courses,classes , cnt , current_course);
               treeNode<int,AVLTree<int,int>> *current_course_parent = current_course;
               //go Rightsss
                current_course=current_course->Right;
                auxCoursesInOrder(numOfClasses,courses,classes,cnt,current_course);
               //
//               while(cnt<numOfClasses && current_course->Right!= nullptr)
//               {
//                   current_course = current_course->Right;
//                   getAllCourseClasses(numOfClasses,courses,classes , cnt , current_course);
//               }
               current_course=current_course_parent->Up;
            }
            if(current_list== nullptr && cnt<numOfClasses)
            {
                return FAILURE;
            }
        }

        //enddd
        return SUCCESS;
    } catch (std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
}


#endif //HW1_COURSESMANAGER_H
