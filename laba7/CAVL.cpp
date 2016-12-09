//
// Created by moskov on 05.12.16.
//

#include "CAVL.h"

template <typename T>
void CAVL<T>::free_tree(AVL_Node<T> * &tmp) {
    if(tmp) {
        free_tree(tmp->left);
        free_tree(tmp->right);
        delete tmp;
    }
}
template <typename T>
CAVL<T>::~CAVL() {
    free_tree(head);
    count_of_element = 0;
    head = NULL;
}
template <typename T>
void CAVL<T>::Insert(T x) {
    AVL_Node<T> * tmp = new AVL_Node<T>(x);
    add_to_avl(head, tmp);
}
template <typename T>
bool CAVL<T>::Remove(T x) {
    return delete_from_avl(head, x);

}
template <typename T>
int CAVL<T>::height(AVL_Node<T> *t) {
    return t == NULL ? 0 : t->h;
}
template <typename T>
int CAVL<T>::difference_of_h(AVL_Node<T> *t) {
    return height(t->right) - height(t->left);
}
template <typename T>
int CAVL<T>::cnt_value(AVL_Node<T> * t) {
    return t == NULL ? 0 : t->cnt;
}
template <typename T>
T CAVL<T>::key_value(AVL_Node<T> * t) {
    return t == NULL ? (0) : t->key;/////////что это?////////////////TODO
}
template <typename T>
void CAVL<T>::right(AVL_Node<T> * &t) {
    AVL_Node<T>* tmp = t->left;
    int a, b, c;
    a = cnt_value(t->right);
    b = cnt_value(tmp->left);
    c = cnt_value(tmp->right);
    t->left = tmp->right;
    tmp->right = t;
    t->h = max(height(t->left), height(t->right)) + 1;
    t->cnt = a + c + 1;
    tmp->h = max(height(tmp->left), height(tmp->right)) + 1;
    //tmp->cnt = cnt_value(tmp->left) + cnt_value(tmp->right) + 1;
    tmp->cnt = a + b + c + 2;
    t = tmp;
}
/*AVL_Node<T>* right(AVL_Node<T>* p) // правый поворот вокруг p
{
	AVL_Node<T>* q = p->left;
	p->left = q->right;
	q->right = p;
    p->h = max(height(p->left), height(p->right)) + 1;
    q->h = max(height(q->left), height(q->right)) + 1;
	return q;
}
AVL_Node<T>* left(AVL_Node<T>* q) // левый поворот вокруг q
{
	AVL_Node<T>* p = q->right;
	q->right = p->left;
	p->left = q;
    q->h = max(height(q->left), height(q->right)) + 1;
    p->h = max(height(p->left), height(p->right)) + 1;
	return p;
}
*/
template <typename T>
void CAVL<T>::left(AVL_Node<T> * &t)
{
    AVL_Node<T>* tmp = t->right;
    int a, b, c;
    a = cnt_value(t->left);
    b = cnt_value(tmp->left);
    c = cnt_value(tmp->right);
    t->right = tmp->left;
    tmp->left = t;
    t->h = max(height(t->left), height(t->right)) + 1;
    t->cnt = a + b + 1;
    tmp->h = max(height(tmp->left), height(tmp->right)) + 1;
    //tmp->cnt = cnt_value(tmp->left) + cnt_value(tmp->right) + 1;
    tmp->cnt = a + b + c + 2;

    t = tmp;
}
template <typename T>
void CAVL<T>::balance(AVL_Node<T>* &t) // балансировка узла p
{
    t->h = max(height(t->left), height(t->right)) + 1;
    t->cnt = cnt_value(t->left) + cnt_value(t->right) + 1;
    if(difference_of_h(t) == 2)
    {
        if(difference_of_h(t->right) < 0)
            right(t->right);
        return left(t);
    }
    if(difference_of_h(t) == (-2))
    {
        if(difference_of_h(t->left) > 0)
            left(t->left);
        return right(t);
    }
}
template <typename T>
int CAVL<T>::Memory() {
    //cout << count_of_element << endl;
    return count_of_element * sizeof(*head);
}
template <typename T>
void CAVL<T>::add_to_avl(AVL_Node<T>* &t, AVL_Node<T>* tmp) {
    if(t == NULL) {
        t = tmp;
        count_of_element++;
        return;
    }
    if(t->key == tmp->key) {
        //cout << "ok";
        t->key.count++;
        return;
    }
    if(t->key < tmp->key) {
        add_to_avl(t->right, tmp);
    }
    else {
        add_to_avl(t->left, tmp);
    }
    balance(t);
    t->cnt++;
    //cout << t->key << " " << t->cnt << " " << cnt_value(t->left) << endl;
    //AVL_Node<T>* tl = t->left;
    //AVL_Node<T>* tr = t->right;
    //if(tl != NULL) { t->cnt += tl->cnt; }
    //if(tr != NULL) { t->cnt += tr->cnt; }
    //t->cnt = tl->cnt + tr->cnt;
}
template <typename T>
AVL_Node<T>* CAVL<T>::findmin(AVL_Node<T>* t) {
    return t->left == NULL ? t : findmin(t->left);
}
template <typename T>
AVL_Node<T>* CAVL<T>::removemin(AVL_Node<T>* t) {
    if( t->left == NULL)
        return t->right;
    t->left = removemin(t->left);
    balance(t);
    return t;
}
template <typename T>
bool CAVL<T>::delete_from_avl(AVL_Node<T>* &t, T x) {
    if(t == NULL) { return false; }
    if(x < t->key) {
        delete_from_avl(t->left, x);
    } else if(x > t->key) {
        delete_from_avl(t->right, x);
    } else {
        if(--t->key.count == 0) {
            AVL_Node<T> *i = t->left;
            AVL_Node<T> *j = t->right;
            count_of_element--;
            delete t;
            t = NULL;
            if (j == NULL) {
                t = i;
                return true;
            }
            AVL_Node<T> *m = findmin(j);
            m->right = removemin(j);
            m->left = i;
            balance(m);
            t = m;
        }
    }
    t->cnt--;
    balance(t);
    return true;
}

template <typename T>
bool CAVL<T>::Search(T x) {
    AVL_Node<T> *tmp = head;
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