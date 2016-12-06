//
// Created by moskov on 05.12.16.
//

#ifndef LABA7_LIBRARY_H
#define LABA7_LIBRARY_H

#pragma once

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define LEN_WORD 256
#define CONSOL_SIZE 128
using namespace std;

extern int compare_count;

template <typename T>
class Data {
public:
    T value;
    int count;
    Data(T tmp) {
    value = tmp;
    count = 1;
    }
    Data() {
        count = 0;
    }
    Data<T>(Data<T> const &obj) {
        cout << "copy_data:" << obj << endl;
        value = obj.value;
        count = obj.count;
    }
    Data<T>& operator = (Data<T> const &obj) {
        cout << "ko";
        if(this != &obj) {
            value = obj.value;
            count = obj.count;
        }
        return *this;
    }
    int print_width() {
        int res = 3;
        int copy = count;
        while(copy > 0) {
            res++;
            copy /= 10;
        }
        return res;
    }
    template <typename X>
    friend unsigned int hash_function(Data<X> const & obj);

    template <typename X>
    friend std::ostream & operator <<(std::ostream & os, Data<X> const & n);

    friend bool operator ==(Data const & a, Data const & b) {
        compare_count++;
        return a.value == b.value;
    }
    friend bool operator !=(Data const & a, Data const & b) {
        return !(a == b);
    }
    friend bool operator <(Data const & a, Data const & b) {
        compare_count++;
        return a.value < b.value;
    }
    friend bool operator >(Data const & a, Data const & b)
    {
        return b < a;
    }

    friend bool operator <=(Data const & a, Data const & b)
    {
        return !(a > b);
    }

    friend bool operator >=(Data const & a, Data const & b)
    {
        return !(a < b);
    }
};

template <typename T>
std::ostream & operator <<(std::ostream & os, Data<T> const & n)
{
os << n.value << "(" << n.count << ")";
}

extern unsigned int hash_function(Data<char> const & obj);


#endif //LABA7_LIBRARY_H
