//
// Created by moskov on 10.10.16.
//

#ifndef LABA2_STACK_LIST_H
#define LABA2_STACK_LIST_H
#define START_SIZE 1000
#define MAX_LEN_WORD 50
#define MAX_MEMORY 1000
#include <stdio.h>
#include <cstring>
#include <assert.h>
#include <iostream>
using namespace std;


typedef struct Node {
    char value[MAX_LEN_WORD];
    Node* next;
} my_list;


my_list *create_node(char* x);
my_list *add_to_list(my_list *tmp, my_list *head);
void free_all(my_list *head);
void print_list(my_list *head);
void print_adr(my_list *head);


class Stack_list {
private:
    my_list *head;
    int len;
    int max_size;
public:
    Stack_list();
    ~Stack_list();
    char* pop();
    void push(char* x);
    bool empty();
    bool is_full();
    void show();
    void show_adr();

};


#endif //LABA2_STACK_LIST_H
