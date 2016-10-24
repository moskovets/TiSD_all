//
// Created by moskov on 23.10.16.
//

#ifndef LABA4_CQUEUE_ARRAY_H
#define LABA4_CQUEUE_ARRAY_H

#include "library.h"


class CQueue_array {
    private:
        request* arr = NULL;
        int back;
        int front;
        int max_size;
        info_queue_request info;
        void increase();
    public:
        CQueue_array();
        CQueue_array(const CQueue_array &);
        ~CQueue_array();
        request PopFront();
        void PushBack(request x);
        bool Empty_CQueue();
        CQueue_array& operator= (const CQueue_array &obj);
        request * get_arr();
        void show();
        void show_adr() {}
        bool is_full();
};


#endif //ALGO4_CQUEUE_ARRAY_H
