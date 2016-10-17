//
// Created by moskov on 17.10.16.
//

#include "Table_key.h"

Table_key::Table_key() {
    id = 0;
    population = 0;
}
Table_key::Table_key(int i, MyRecord &obj) {
    id = i;
    population = obj.get_population();
}

void buble_sort(Table_key *begin, Table_key* end) {

    for (Table_key *i = begin; i < end; i++) {
        for (Table_key *j = i + 1; j < end; j++) {
            if (i->population > j->population) {
                Table_key tmp = *j;
                *j = *i;
                *i = tmp;
            }
        }
    }
}
void quick_sort(Table_key *begin, Table_key* end) {
    Table_key *i = begin, *j = end, x = *(i + (j - i) / 2);

    do {
        while (i->population < x.population) i++;
        while (j->population > x.population) j--;

        if(i <= j) {
            if (i->population > j->population) {
                Table_key tmp = *j;
                *j = *i;
                *i = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < end)
        quick_sort(i, end);
    if (begin < j)
        quick_sort(begin, j);
}
