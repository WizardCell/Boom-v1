//
// Created by basil on 12/3/2020.
//
#include "library.h"
#include "CoursesManager.h"

void *Init()
{
    CoursesManager *DS = new CoursesManager ();
    return (void*)DS;
}

StatusType AddCourse (void *DS, int courseID, int numOfClasses)
{
    return ((CoursesManager *)DS)-> AddCourseManger(DS,courseID, numOfClasses);
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    return ((CoursesManager *)DS)->TimeViewedManger(DS,courseID,classID,timeViewed);
}

StatusType RemoveCourse(void *DS, int courseID)
{
    return ((CoursesManager *)DS)->RemoveCourseManger(DS,courseID);
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    return ((CoursesManager *)DS)-> WatchClassManger(DS,courseID, classID,time);
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    return ((CoursesManager *)DS)-> GetMostViewedClassesManger(DS,numOfClasses, courses,classes);
}

void Quit(void** DS)
{
    delete (CoursesManager*)(*DS) ;
    *DS = nullptr ;
}