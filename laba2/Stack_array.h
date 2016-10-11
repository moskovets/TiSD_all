//
// Created by moskov on 10.10.16.
//

#ifndef LABA2_STACK_ARRAY_H
#define LABA2_STACK_ARRAY_H
#define START_SIZE 1000
#define MAX_LEN_WORD 50
#include <cstring>
#include <assert.h>
#include <iostream>
using namespace std;
class Stack_array {
private:
    char** arr;
    int top;
    int max_size;
    void increase();
public:
    Stack_array();
    Stack_array(const Stack_array &);
    ~Stack_array();
    char* pop();
    void push(char* x);
    bool empty();
    bool is_full();
    char** get_arr();
    void show();
};


#endif //LABA2_STACK_ARRAY_H
