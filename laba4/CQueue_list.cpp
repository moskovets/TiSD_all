//
// Created by moskov on 23.10.16.
//

#include "CQueue_list.h"
/*
    функция создания новой структуры
    возвращает NULL при неуспешном выделении памяти
*/

my_list *create_node(request x)
{
    my_list *a = new my_list;
    if (a)
    {
        a->value = x;
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
void free_all(my_list *head, my_list* memory[], int m)
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
void print_adr(my_list *head) {
    if(head) {
        print_adr(head->next);
        cout <<  head << " ";
    }
}

CQueue_list::CQueue_list()
{
    head = NULL;
    tail = NULL;
    info = info_queue_request();
    m = 0;
}


CQueue_list::~CQueue_list()
{
    free_all(head, memory, m);
    //cout << "~ " << endl;
}

void CQueue_list::PushBack(request x)
{
    my_list *tmp = create_node(x);
    if (tmp == NULL) {
        cout << "Cannot allocate memory";
        return;
    }
    if(head == NULL && tail == NULL) {
        tail = head = tmp;
    }
    else {
        tail->next = tmp;
        tail = tail->next;
    }
    int j = 0;
    for(int i = 0; i < m-j; i++) {
        if(memory[i] == tmp) {
            j++;
        }
        memory[i] = memory[i+j];
    }
    m -= j;
    info.in_request++;
    info.count_request++;
    info.tmp_size++;
    info.sum_size += info.tmp_size;
}
request CQueue_list::PopFront() {
    request x;
    assert(info.tmp_size > 0);
    x = head->value;
    my_list* tmp = head->next;
    memory[m] = head;
    m++;
    delete head;
    head = tmp;
    info.tmp_size--;
    info.sum_size += info.tmp_size;
    info.count_request++;
    info.out_request++;
    //x.time_out = time_out;
    //info.sum_time += time_out - x.time_in;
    if(info.tmp_size == 0) { head = tail = NULL; }
    return x;
}

bool CQueue_list::Empty_CQueue()
{
    return head == NULL;
}
void CQueue_list::show_adr()
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
/*
 * информацию о текущей и средней длине очереди,
 *
 */
void CQueue_list::show() {

    cout << "Текущая длина очереди: " << info.tmp_size << endl;
    cout << "Средняя длина очереди: " << (double) info.sum_size / (double) info.count_request << endl;
    //cout << "Кол-во вошедших заявок: " << info.in_request << endl;
    //cout << "Кол-во вышедших заявок: " << info.out_request << endl;
    //cout << "Средне время пребывания в очереди: " << (double) info.sum_time / (double) info.out_request << endl;
}
bool CQueue_list::is_full() {
    return info.tmp_size >= START_SIZE;
}
