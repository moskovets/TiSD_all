//
// Created by moskov on 05.12.16.
//

#include "CHashTableClose.h"
template <typename T>
void CHashTableClose<T>::Show() {
    for (int i = 0; i < tableSize; i++) {
        cout << i << ":";
        if(status[i] == 1) {
            cout << table[i];
        }
        cout << endl;
    }
}

template <typename T>
CHashTableClose<T>::CHashTableClose(int Start_size) {
    tableSize = Start_size;
    table = new T[tableSize];
    status = new short int[tableSize]; // 0 - pusto, 1 - is, 2 - del
    for (int i = 0; i < tableSize; ++i) {
        status[i] = 0;
    }
    count_of_elem = 0;
}
template <typename T>
int CHashTableClose<T>::Memory() {
    return tableSize * sizeof(T);
}
template <typename T>
CHashTableClose<T>::~CHashTableClose() {
    delete[] table;
    delete[] status;
}

template <typename T>
void CHashTableClose<T>::New_Table(int new_size) {
    assert(new_size > tableSize);
    T* A = new T[count_of_elem];
    int current = 0;
    for (int i = 0; i < tableSize; ++i) {
        if (status[i] == 1 && table[i].count > 0) {
            A[current] = table[i];
            current++;
        }
    }
    delete[] table;
    delete[] status;
    table = new T[new_size];
    status = new short int[new_size]; // 0 - pusto, 1 - is, 2 - del
    tableSize = new_size;
    for (int i = 0; i < new_size; ++i) {
        status[i] = 0;
    }
    count_of_elem = 0;
    current--;
    while (current >= 0) {
        for(int j = 0; j < A[current].count; j++)
            Insert(A[current].value);
        current--;
    }
    delete[] A;
}

template <typename T>
bool CHashTableClose<T>::Insert(T k) {
    unsigned int h = hash_function(k) * 2 + 1;
    for (unsigned int i = 0; i < tableSize; ++i) {
        unsigned int j = (i * h) % tableSize;
        if (status[j] == 1 && table[j] == k) {
            table[j].count++;
            return false;
        }
        if (status[j] != 1) {
            table[j] = k;
            count_of_elem++;
            status[j] = 1;
            if (4 * count_of_elem > 3 * tableSize) {
                New_Table(tableSize * 2);
            }
            return true;
        }
    }
    return false;
}

template <typename T>
bool CHashTableClose<T>::Search(T x) {
    unsigned int h = hash_function(x) * 2 + 1;
    for (int i = 0; i < tableSize; ++i) {
        unsigned int j = (i * h) % tableSize;
        if (status[j] == 0) {
            return false;
        }
        if (status[j] == 1 && table[j] == x) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool CHashTableClose<T>::Delete_element(T x) {
    unsigned int h = hash_function(x) * 2 + 1;
    for (int i = 0; i < tableSize; ++i) {
        unsigned int j = (i * h) % tableSize;
        if ((status[j] == 1) && (table[j] == x)) {
            table[j].count--;
            if(table[j].count == 0) {
                status[j] = 2;
                count_of_elem--;
            }
            return true;
        }
        if (status[j] == 0) {
            return false;
        }
    }
    return false;
}
