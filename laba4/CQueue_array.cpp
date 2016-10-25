//
// Created by moskov on 23.10.16.
//

#include "CQueue_array.h"
CQueue_array::CQueue_array()
{
    //cout << "const" << endl;
    max_size = START_SIZE;
    info.count_request = info.sum_size = info.tmp_size = 0;
    info.sum_time = info.out_request = info.in_request = 0;
    back = front = 0;
    arr = new request[max_size];
}
CQueue_array::CQueue_array(const CQueue_array &obj)
{
    if(this != &obj) {
        *this = obj;
    }
}
CQueue_array& CQueue_array::operator=(const CQueue_array &obj)
{
    //cout << "=";
    if(this != &obj) {
        max_size = obj.max_size;
        front = obj.front;
        back = obj.back;
        info = obj.info;
        if(arr) delete[] arr;
        arr = new request[obj.max_size];  //Выделяю память для элемента объекта
        for (int i = 0; i < max_size; i++) {
            arr[i] = obj.arr[i]; //Поэлементно копирую каждый элемент из принимаемого объекта в текущий
        }
        max_size=obj.max_size;
    }
    return *this;
}
CQueue_array::~CQueue_array() {
    //cout << "~ " << endl;
    if(arr) {
        //cout << "del";
        delete[] arr;
    }
}
void CQueue_array::increase() {
    //cout << "in" << endl;
    request * arr_copy = new request[max_size * 2];
    int j = 0;
    int i = back;
    while(i != front) {
        arr_copy[j] = arr[i];
        j++;
        i++;
        i %= max_size;
    }
    back = 0;
    front = j;
    delete[] arr;
    arr = arr_copy;
    max_size *= 2;
}
void CQueue_array::PushBack(request x) {
    /*
     * if(front == (back - 1 + max_size) % max_size) {
        increase();
    }*/
    info.tmp_size++;
    info.sum_size += info.tmp_size;
    info.count_request++;
    info.in_request++;
    back--;
    back += max_size;
    back %= max_size;
    arr[back] = x;
}
request CQueue_array::PopFront() {
    request x;
    assert(back != front);
    info.tmp_size--;
    info.sum_size += info.tmp_size;
    info.count_request++;
    info.out_request++;
    front--;
    front += max_size;
    front %= max_size;
    x = arr[front];
    //x.time_out = time_out;
    //info.sum_time += time_out - x.time_in;
    return x;
}
bool CQueue_array::Empty_CQueue()
{
    return back == front;
}
request * CQueue_array::get_arr()
{
    return arr;
}
bool CQueue_array::is_full() {
    return front == (back - 1 + max_size) % max_size;
}
/*
 * информацию о текущей и средней длине очереди,
 * количестве вошедших и вышедших заявок и о среднем времени пребывания заявок в очереди.
 */
void CQueue_array::show() {

    cout << "Текущая длина очереди: " << info.tmp_size << endl;
    cout << "Средняя длина очереди: " << (double) info.sum_size / (double) info.count_request << endl;
    //cout << "Кол-во вошедших заявок: " << info.in_request << endl;
    //cout << "Кол-во вышедших заявок: " << info.out_request << endl;
    //cout << "Средне время пребывания в очереди: " << (double) info.sum_time / (double) info.out_request << endl;
}