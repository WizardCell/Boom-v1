//
// Created by basil on 12/2/2020.
//

#ifndef HW1_CLASSLECTURE_H
#define HW1_CLASSLECTURE_H
template<class Data_type>
class classLecture {
public:
    int class_id;
    int constant_number_of_class;
    Data_type* class_time_node;
    classLecture()
    {
        this->class_id = 0;
        this->constant_number_of_class=0;
        this->class_time_node = nullptr;
    }
    classLecture(int id)
    {
        this->class_id = id;
        this->class_time_node = nullptr;
    }
    ~classLecture()= default;
};

#endif //HW1_CLASSLECTURE_H
