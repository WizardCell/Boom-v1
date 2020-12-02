//
// Created by basil on 12/2/2020.
//

#ifndef HW1_CLASSLECTURE_H
#define HW1_CLASSLECTURE_H
template<class Data_type>
class classLecture {
public:
    int class_id;
    Data_type* class_time_node;
    classLecture(int id)
    {
        this->class_id = id;
        this->class_time_node = nullptr;
    }
    ~classLecture()= default;
};

#endif //HW1_CLASSLECTURE_H
