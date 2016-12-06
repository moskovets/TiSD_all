//
// Created by moskov on 05.12.16.
//

#ifndef LABA7_CHASHTABLECLOSE_H
#define LABA7_CHASHTABLECLOSE_H
#include "library.h"

template <class T>
class CHashTableClose
{
private:
    T* table;
    short int* status; // 0 - pusto, 1 - is, 2 - del
    int tableSize;
    int count_of_elem;
public:
    CHashTableClose(int Start_size);
    ~CHashTableClose();
    void New_Table(int new_size);
    bool Insert(T k);
    bool Search_element(T x);
    bool Delete_element(T x);
    void Show();
};

#endif //LABA7_CHASHTABLECLOSE_H
