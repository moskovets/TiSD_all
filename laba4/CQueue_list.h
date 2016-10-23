//
// Created by moskov on 23.10.16.
//

#ifndef LABA4_CQUEUE_LIST_H
#define LABA4_CQUEUE_LIST_H

#include "library.h"

typedef struct Node {
    request value;
    Node* next;
} my_list;


my_list *create_node(request x);
my_list *add_to_list(my_list *tmp, my_list *head);
void free_all(my_list *head);
void print_adr(my_list *head);


class CQueue_list {
private:
    my_list *head;
    my_list *tail;
    info_queue_request info;
public:
    CQueue_list();
    ~CQueue_list();
    void show();
    void show_adr();
    request PopFront();
    void PushBack(request x);
    bool Empty_CQueue();
};


#endif //ALGO4_CQUEUE_LIST_H
