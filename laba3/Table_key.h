//
// Created by moskov on 17.10.16.
//

#ifndef LABA3_TABLE_KEY_H
#define LABA3_TABLE_KEY_H

#include "MyRecord.h"

class Table_key {
public:
    int id;
    long int population;
    Table_key();
    Table_key(int i, MyRecord &obj);
};

//sort 1, sort 2
void buble_sort(Table_key *begin, Table_key* end);
void quick_sort(Table_key *begin, Table_key* end);
#endif //LABA3_TABLE_KEY_H
