#include <iostream>
#include "CoursesManager.h"
int main()
{
    std::cout << "Hello, World!" << std::endl;
    CoursesManager *ds = new  CoursesManager();
    ds->AddCourse(ds,234218,3);
    std::cout<< *ds->courses_tree->getRoot()->Key << std::endl;
    delete ds;
    return 0;
}
