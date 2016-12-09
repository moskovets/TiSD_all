//
// Created by moskov on 05.12.16.
//

#ifndef LABA7_CCHashTableOpenOPEN_H
#define LABA7_CCHashTableOpenOPEN_H

#include "library.h"

template <typename T>
struct ElementTable {
    T value;
    ElementTable<T>* next = NULL;
    ElementTable() {}
    ElementTable(T x) {
        value = x;
        next = NULL;
    }
};

template <class T>
class CHashTableOpen
{
private:
    ElementTable<T>** table;
    bool* status; // 0 - pusto, 1 - is
    int tableSize;
    int count_of_elem;
public:
    CHashTableOpen(int Start_size);
    ~CHashTableOpen();
    void New_Table(int new_size);
    bool Insert(T k);
    bool Search(T x);
    int Memory();
    bool Delete_element(T x);
    void Show();
};

#endif //LABA7_CCHashTableOpenOPEN_H
