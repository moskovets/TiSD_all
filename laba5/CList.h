//
// Created by moskov on 03.11.16.
//

#ifndef LABA5_CLIST_H
#define LABA5_CLIST_H

#include "library.h"
typedef struct Node {
    int value;
    Node* next;
} my_list;

my_list *create_node(int x);
my_list *copy_list(my_list *head);
my_list *add_to_list(my_list *tmp, my_list *head);
void free_all(my_list *head);
void print_list(my_list *head);

//void print_adr(my_list *head);

#endif //LABA5_CLIST_H
