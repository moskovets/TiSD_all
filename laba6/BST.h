//
// Created by moskov on 12.11.16.
//

#ifndef LABA6_BST_H
#define LABA6_BST_H
#include "library.h"

struct element {
    char word[LEN_WORD];
    element *left = NULL;
    element *right = NULL;
    element(char *str) {
        assert(strlen(str) < LEN_WORD);
        strcpy(word, str);
        left = NULL;
        right = NULL;
    }

};
//Binary search tree
class BST {
private:
    element *head = NULL;
    bool printable = true;
    void print(element* tmp, int deep, bool flag, char c = '\0');
    void delete_tree(element* tmp);
    int for_find_letter(element* tmp, char c = '\0');
    void operator_copy(element **head, element *tmp);
    void print_tree(element *h, char c = '\0');
    void RootLR(element *tmp);
    void LRootR(element *tmp);
    void LRRoot(element *tmp);
    void delete_remove(element* prev, element *tmp);
public:
    BST(const BST &obj);
    BST();
    int find_letter(char c);

    BST& operator=(const BST& obj);
    void insert(char *str);
    bool remove(char *str);
    ~BST();
    void show(char c = '\0');
    void show_as_tree(char c = '\0');

    bool find(char *str);
    void RootLeftRight();
    void LeftRootRight();
    void LeftRightRoot();

};
void probel(int n);
void log(const char *str);

#endif //LABA6_BST_H
