//
// Created by moskov on 05.12.16.
//

#ifndef LABA7_CBST_H
#define LABA7_CBST_H

#include "library.h"
template <typename T>
struct element {
    T key;
    element *left = NULL;
    element *right = NULL;
    element(T x) {
        //cout << "element:" << x << endl;
        key = T(x);
        left = NULL;
        right = NULL;
    }

};
//Binary search tree
template <typename T>
class CBST {
private:
    element<T> *head = NULL;
    int count_of_element = 0;
    void delete_tree(element<T>* tmp);
    void operator_copy(element<T> **head, element<T> *tmp);
    void delete_remove(element<T>* prev, element<T> *tmp);
public:
    CBST(const CBST &obj);
    CBST();
    CBST<T>& operator=(const CBST& obj);
    void Insert(T x);
    bool Remove(T x);
    bool Search(T x);
    ~CBST();
    template <typename X>
    friend void print(X *tmp, int deep, bool flag);
    template <typename X>
    friend void show_as_tree(X* tree);
    template <typename X>
    friend void show(X* tree);
    int Memory();

    };

#endif //LABA7_CBST_H
