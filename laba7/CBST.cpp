//
// Created by moskov on 05.12.16.
//

#include "CBST.h"
extern void log(const char *str);

template <typename T>
CBST<T>& CBST<T>::operator=(const CBST<T> &obj) {
    log("=");
    operator_copy(&head, obj.head);
}
template <typename T>
void CBST<T>::operator_copy(element<T> **head, element<T> *tmp) {
    log("copy");
    element<T> *a = *head;
    if(tmp) {
        a = new element<T>(tmp->key);
        operator_copy(&a->left, tmp->left);
        operator_copy(&a->right, tmp->right);
    }
}
template <typename T>
void CBST<T>::Insert(T x) {
    log("insert");
    cout << x << endl;
    element<T> *new_elem = new element<T>(x);
    cout << new_elem->key << endl;
    element<T> *tmp = head;
    if(!head) {
        head = new_elem;
        return;
    }
    while(1) {
        if(!tmp) {
            tmp = new_elem;
            break;
        }
        if(tmp->key == x) {
            tmp->key.count++;
            break;
        }
        if(tmp->key < x) {
            if(tmp->right) {
                tmp = tmp->right;
            }
            else {
                tmp->right = new_elem;
                break;
            }
        }
        else {
            if(tmp->left) {
                tmp = tmp->left;
            }
            else {
                tmp->left = new_elem;
                break;
            }
        }
    }
}
template <typename T>
void CBST<T>::delete_remove(element<T>* prev, element<T> *tmp) {
    element<T> *b = NULL;
    int flag = 0;
    if((!tmp->left) && (!tmp->right)) {
        b = NULL;
        flag = 1;
    }
    if(tmp->left && !tmp->right) {
        b = tmp->left;
        flag = 1;
    }
    if(!tmp->left && tmp->right) {
        b = tmp->right;
        flag = 1;
    }
    if(flag) {
        if(prev == NULL || prev == tmp) {
            head = b;
        }
        else {
            if(prev->left == tmp) {
                prev->left = b;
            }
            else if(prev->right == tmp){
                prev->right = b;
            }
        }
        delete tmp;
        return;
    }
    element<T>* a = tmp->right;
    element<T>* new_elem = tmp;
    while(a) {
        if(a->left) {
            new_elem = a;
            a = a->left;
        }
        else {
            break;
        }
    }
    tmp->key = a->key;
    if(new_elem->left == a) {
        new_elem->left = a->right;
    }
    else {
        new_elem->right = a->right;
    }
    delete a;
}
template <typename T>
bool CBST<T>::Remove(T x) {
    element<T> *tmp = head;
    element<T> *prev = NULL;
    int cmp = 0;
    while(1) {
        if(!tmp) {
            return false;
        }
        if(x == tmp->key) {
            tmp->key.count--;
            if(tmp->key.count == 0)
                delete_remove(prev, tmp);
            return true;
        }
        prev = tmp;
        if(x < tmp->key) {
            if(tmp->right) {
                tmp = tmp->right;
            }
            else {
                return false;
            }
        }
        else {
            if(tmp->left) {
                tmp = tmp->left;
            }
            else {
                return false;
            }
        }
    }

}
template <typename T>
CBST<T>::~CBST() {
    log("~");
    delete_tree(head);
    head = NULL;
}
template <typename T>
void CBST<T>::delete_tree(element<T> *tmp) {
    if(tmp) {
        delete_tree(tmp->left);
        delete_tree(tmp->right);
        delete tmp;
        tmp = NULL;
    }
}
template <typename T>
CBST<T>::CBST(const CBST &obj) {
    log("copy");
    if(&obj != this) {
        *this = obj;
    }
}
template <typename T>
CBST<T>::CBST() {
    head = NULL;
}
template <typename T>
bool CBST<T>::Search(T x) {
    element<T> *tmp = head;
    while(tmp) {
        if(tmp->key == x) {
            return true;
        }
        if(tmp->key < x) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }
    return false;
}