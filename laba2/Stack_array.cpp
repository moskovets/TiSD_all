//
// Created by moskov on 10.10.16.
//

#include "Stack_array.h"
Stack_array::Stack_array()
{
    max_size = START_SIZE;
    top = 0;
    arr = new char* [max_size]; //(int*) malloc(max_size * sizeof(int));
    for(int i = 0; i < max_size; ++i) {
        arr[i] = new char[MAX_LEN_WORD];
    }
}

Stack_array::Stack_array(const Stack_array &obj)
{
    max_size = obj.max_size;
    top = obj.top;
    if(arr) {
        for(int i = 0; i < max_size; ++i) {
            delete [] arr[i];
        }
        delete[] arr;
    }
    arr = new char* [max_size]; //(int*) malloc(max_size * sizeof(int));
    for(int i = 0; i < max_size; ++i) {
        arr[i] = new char[MAX_LEN_WORD];
    }
    for (int i = 0; i < max_size; i++) {
        for (int j = 0; j < MAX_LEN_WORD; ++j) {
            arr[i][j] = obj.arr[i][j]; //Поэлементно копирую каждый элемент из принимаемого объекта в текущий
        }
    }
    max_size=obj.max_size; //скопировать нужно каждый кусочек класса, сами они не копируются
}

Stack_array::~Stack_array()
{
    for(int i = 0; i < max_size; ++i) {
        delete [] arr[i];
    }
    delete[] arr;
    //cout << "~ " << endl;
}

void Stack_array::increase()
{
    char** arr_copy = new char* [max_size * 2];
    for(int i = 0; i < max_size * 2; ++i) {
        arr_copy[i] = new char[MAX_LEN_WORD];
    }
    for (int i = 0; i < max_size; i++) {
        for (int j = 0; j < MAX_LEN_WORD; ++j) {
            arr_copy[i][j] = arr[i][j];
        }
    }
    for(int i = 0; i < max_size; ++i) {
        delete [] arr[i];
    }
    delete[] arr;
    max_size *= 2;
}

void Stack_array::push(char* x)
{
    assert(strlen(x) < MAX_LEN_WORD && top < max_size);
    strcpy(arr[top], x);
    top++;
    //if(top >= max_size) { increase(); }
}
char* Stack_array::pop()
{
    char *x = new char[MAX_LEN_WORD];
    if(top == 0) { return 0; }
    strcpy(x, arr[top - 1]);
    top--;
    return x;
}

bool Stack_array::empty()
{
    return !top;
}
char** Stack_array::get_arr()
{
    return arr;
}
void Stack_array::show()
{
    int i;
    if(top == 0) { cout << "Stack is empty!"; }
    for(i = 0; i < tыop; i++) { cout << arr[i] << " "; }
    cout << endl;
}
bool Stack_array::is_full() {
    return top >= max_size;
}