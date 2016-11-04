//
// Created by moskov on 03.11.16.
//

#include "CList.h"
my_list *create_node(int x)
{
    my_list *a = new my_list;
    if (a)
    {
        a->value = x;
        a->next = NULL;
    }
    return a;
}
my_list *copy_list(my_list *head) {
    if(!head)
        return NULL;
    my_list* first = create_node(head->value);
    my_list* last = first->next;
    my_list* prev = first;
    for(my_list *tmp = head->next; tmp; tmp = tmp->next) {
        last = create_node(tmp->value);
        prev->next = last;
        prev = prev->next;
        last = last->next;
    }
    return first;
}

my_list *add_to_list(my_list *tmp, my_list *head)
{
    if (!head)
    {
        head = tmp;
        return head;
    }
    tmp->next = head;
    head = tmp;
    return head;
}
void free_all(my_list *head)
{
    my_list *next;
    for (; head; head = next)
    {
        next = head->next;
        delete head;
    }
}
void print_list(my_list *head) {
    if(head) {
        cout << head->value << " ";
        print_list(head->next);
    }
}
