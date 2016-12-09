//
// Created by moskov on 05.12.16.
//

#include "CHashTableOpen.h"
template <typename T>
void CHashTableOpen<T>::Show() {
    for (int i = 0; i < tableSize; i++) {
        cout << i << ":";
        if(status[i]) {
            ElementTable<T> *tmp = table[i];
            while(tmp) {
                cout << tmp->value << " ";
                tmp = tmp->next;
            }
        }
        cout << endl;
    }
}

template <typename T>
CHashTableOpen<T>::CHashTableOpen(int Start_size) {
    tableSize = Start_size;
    table = new ElementTable<T>* [tableSize];
    status = new bool[tableSize]; // 0 - pusto, 1 - is
    //cout << "I was here" << endl;
    for (int i = 0; i < tableSize; ++i) {
        status[i] = 0;
        table[i] = NULL;
    }
    count_of_elem = 0;
}

template <typename T>
CHashTableOpen<T>::~CHashTableOpen() {
    for(int i = 0; i < tableSize; i++) {
        ElementTable<T> *t, *tmp = table[i];
        while(tmp) {
            t = tmp->next;
            delete tmp;
            tmp = t;
        }
    }
    delete[] table;
    delete[] status;
}
template <typename T>
int CHashTableOpen<T>::Memory() {
    return sizeof(ElementTable<T>) * count_of_elem;
}
template <typename T>
void CHashTableOpen<T>::New_Table(int new_size) {
    assert(new_size > tableSize);
    queue<ElementTable<T>*> A;
    for(int i = 0; i < tableSize; i++) {
        ElementTable<T> *tmp = table[i];
        while(tmp) {
            A.push(tmp);
            //delete tmp;
            tmp = tmp->next;
        }
    }
    delete[] table;
    delete[] status;

    status = new bool[tableSize]; // 0 - pusto, 1 - is
    table = new ElementTable<T>* [new_size];
    tableSize = new_size;
    for (int i = 0; i < new_size; ++i) {
        status[i] = 0;
        table[i] = NULL;
    }
    count_of_elem = 0;
    while (!A.empty()) {
        for(int j = 0; j < A.front()->value.count; j++) {
            Insert(A.front()->value.value);
        }
        ElementTable<T> *tmp = A.front();
        A.pop();
        delete tmp;
    }
}

template <typename T>
bool CHashTableOpen<T>::Insert(T k) {
    unsigned int h = hash_function(k) % tableSize;
    ElementTable<T> *tmp = table[h];
    if(status[h] == 0 || !tmp) {
        table[h] = new ElementTable<T>(k);
        status[h] = 1;
        count_of_elem++;
        return true;
    }
    if(tmp->value == k) {
        tmp->value.count++;
        return false;
    }
    while(tmp->next) {
        tmp = tmp->next;
        if(tmp->value == k) {
            tmp->value.count++;
            return false;
        }
    }
    tmp->next = new ElementTable<T>(k);
    count_of_elem++;
    if (count_of_elem > 2 * tableSize) {
        New_Table(tableSize * 2);
    }
    return true;
}

template <typename T>
bool CHashTableOpen<T>::Search(T x) {
    unsigned int h = hash_function(x) % tableSize;
    ElementTable<T> *tmp = table[h];
    if(status[h] == 0 || !tmp) {
        return false;
    }
    while(tmp) {
        if(tmp->value == x) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

template <typename T>
bool CHashTableOpen<T>::Delete_element(T k) {
    unsigned int h = hash_function(k) % tableSize;
    ElementTable<T> *tmp = table[h];
    if(status[h] == 0 || !tmp) {
        return false;
    }
    if(tmp->value == k) {
        tmp->value.count--;
        if(tmp->value.count == 0) {
            tmp = tmp->next;
            delete table[h];
            count_of_elem--;
            table[h] = tmp;
            status[h] = 0;
        }
        return true;
    }
    while(tmp->next) {
        //tmp = tmp->next;
        if(tmp->next->value == k) {
            if(--tmp->next->value.count == 0) {
                ElementTable<T> *help = tmp->next->next;
                delete tmp->next;
                count_of_elem--;
                tmp->next = help;
            }
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}
