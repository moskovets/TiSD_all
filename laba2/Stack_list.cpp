//
// Created by moskov on 10.10.16.
//

#include "Stack_list.h"
/*
    функция создания новой структуры
    возвращает NULL при неуспешном выделении памяти
*/
my_list *memory[MAX_MEMORY];
int m;

my_list *create_node(char* x)
{
    my_list *a = new my_list;
    if (a)
    {
        strcpy(a->value, x);
        a->next = NULL;
    }
    return a;
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
        memory[m] = head;
        m++;
        delete head;
    }
}
void print_list(my_list *head) {
    if(head) {
        print_list(head->next);
        cout << head->value << " ";
    }
}
void print_adr(my_list *head) {
    if(head) {
        print_adr(head->next);
        cout <<  head << " ";
    }
}

Stack_list::Stack_list()
{
    max_size = START_SIZE;
    head = NULL;
    len = 0;
    m = 0;
}


Stack_list::~Stack_list()
{
    free_all(head);
    len = 0;
    //cout << "~ " << endl;
}

void Stack_list::push(char* x)
{
    assert(strlen(x) < MAX_LEN_WORD && len < max_size);
    my_list *tmp = create_node(x);
    if (tmp == NULL) {
        cout << "Cannot allocate memory";
        return;
    }
    int j = 0;
    for(int i = 0; i < m-j; i++) {
        if(memory[i] == tmp) {
            j++;
        }
        memory[i] = memory[i+j];
    }
    m -= j;
    head = add_to_list(tmp, head);
    len++;
    //if(top >= max_size) { increase(); }
}
char* Stack_list::pop()
{
    char *x = new char[MAX_LEN_WORD];
    if(len == 0) { return 0; }
    strcpy(x, head->value);
    my_list* tmp = head->next;
    memory[m] = head;
    m++;
    delete head;
    head = tmp;
    len--;
    return x;
}

bool Stack_list::empty()
{
    return !len;
}
void Stack_list::show()
{
    if(len == 0) {
        cout << "Stack is empty!" << endl;
        return;
    }
    print_list(head);
    cout << endl;
    print_adr(head);
    cout << endl;
}
void Stack_list::show_adr()
{
    if(m == 0) {
        cout << "No free memory" << endl;
        return;
    }
    for(int i = 0; i < m; i++) {
        cout << memory[i] << " ";
    }
    cout << endl;
}
bool Stack_list::is_full() {
    return len >= max_size;
}