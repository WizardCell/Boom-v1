
#include "CoursesManager.h"


//
// Created by basil on 12/1/2020.
//

int main()
{
    CoursesManager<int> * ds = new CoursesManager<int>();
    ds->AddCourse(ds,234128,3);
    std::cout<< *(ds->courses_tree->tree_root->Id) << std::endl;
    
    return 0;
}