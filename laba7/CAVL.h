//
// Created by moskov on 05.12.16.
//

#ifndef LABA7_CAVL_H
#define LABA7_CAVL_H
#include "library.h"
template <typename T>
struct AVL_Node {
    AVL_Node* left, *right;
    T key;
    int h;
    int cnt;
    AVL_Node() {
        left = right = NULL;
        h = cnt = 0;
    }
    AVL_Node(T& x) {
        left = right = NULL;
        key = x;
        h = cnt = 1;
    }
};

template <typename T>
class CAVL {
private:
    int height(AVL_Node<T> *t);
    int difference_of_h(AVL_Node<T> *t);
    int cnt_value(AVL_Node<T> * t);
    T key_value(AVL_Node<T> * t);
    void right(AVL_Node<T> * &t);
    void left(AVL_Node<T> * &t);
    void balance(AVL_Node<T>* &t); // балансировка узла p
    void add_to_avl(AVL_Node<T>* &t, AVL_Node<T>* tmp);
    AVL_Node<T>* findmin(AVL_Node<T>* t);
    AVL_Node<T>* removemin(AVL_Node<T>* t);
    bool delete_from_avl(AVL_Node<T>* &t, T x);
    //int value_by_index(AVL_Node* t, int ind);
    //int index(AVL_Node* t, int x);
    void free_tree(AVL_Node<T> * &tmp);
    AVL_Node<T>* head = NULL;
public:
    CAVL() {}
    ~CAVL();
    void Insert(T x);
    bool Remove(T x);
    bool Search(T x);
    template <typename X>
    friend void print(X *tmp, int deep, bool flag);
    template <typename X>
    friend void show_as_tree(X* tree);
    template <typename X>
    friend void show(X* tree);


};
//template<typename T>
//void print(T *tmp, int deep, bool flag);
//template<typename T>
//void show_as_tree(T* tree);

#endif //LABA7_CAVL_H
