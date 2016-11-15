//
// Created by moskov on 12.11.16.
//

#include "BST.h"

#define ANSI_COLOR_RESET   "\x1b[0m"
#define KRED  "\x1B[31m"
void log(const char *str)
{
  ;  //cout << endl << "l: " << str << endl;
}

BST& BST::operator=(const BST &obj) {
    log("=");
    printable = obj.printable;
    operator_copy(&head, obj.head);
}
void BST::operator_copy(element **head, element *tmp) {
    element *a = *head;
    if(tmp)
    {
        a = new element(tmp->word);
        operator_copy(&a->left, tmp->left);
        operator_copy(&a->right, tmp->right);
    }
}
/*char* to_lower(char *str) {
    char tmp[LEN_WORD];
    for(int i = 0; str[i]; i++) {
        tmp[i] = tolower(str[i]);
    }
    return tmp;
}*/
void BST::insert(char *str) {
    element *new_elem = new element(str);
    if(strlen(str) > 6) { printable = false; }
    element *tmp = head;
    if(!head) {
        head = new_elem;
        return;
    }

    while(1) {
        if(!tmp) {
            tmp = new_elem;
            break;
        }
        if(strcmp(tmp->word, str) < 0) {
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
void BST::delete_remove(element* prev, element *tmp) {
    element *b = NULL;
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
        if(prev->left == tmp) {
            prev->left = b;
        }
        else if(prev->right == tmp){
            prev->right = b;
        }
        delete tmp;
        return;
    }
    element* a = tmp->right;
    element* new_elem = tmp;
    while(a) {

        if(a->left) {
            new_elem = a;
            a = a->left;
        }
        else if(a->right) {
            new_elem = a;
            a = a->right;
        }
        else {
            break;
        }
    }
    strcpy(tmp->word, a->word);
    if(new_elem->left == a) {
        new_elem->left = NULL;
    }
    else {
        new_elem->right = NULL;
    }
    delete a;
}
bool BST::remove(char *str) {
    element *tmp = head;
    element *prev = NULL;
    int cmp = 0;
    while(1) {
        if(!tmp) {
            return false;
        }
        cmp = strcmp(tmp->word, str);
        if(cmp == 0) { delete_remove(prev, tmp); return true; }
        prev = tmp;
        if(cmp < 0) {
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
void BST::print(element *tmp, int deep, bool flag, char c) {
    if(tmp) {
        for (int i = 0; i < deep - 1; i++) {
            cout << "|    ";
        }
        if (deep >= 1)
            cout << "|----";
        if(c && tmp->word[0] == c) {
            printf(KRED);
        }
        cout << tmp->word << endl;
        printf(ANSI_COLOR_RESET);
        flag = false;
        if(tmp->left || tmp->right) { flag = true; }
        print(tmp->left, deep + 1, flag, c);
        print(tmp->right, deep + 1, flag, c);
    }
    else if(flag) {
        for (int i = 0; i < deep - 1; i++) {
            cout << "|    ";
        }
        if (deep >= 1)
            cout << "|----";
        cout << "-----" << endl;
    }
}
void BST::print_tree(element *h, char c) {
    queue<element *> A;
    A.push(h);
    element *tmp = NULL;
    int level = 0;
    int flag = 1;
    //probel(5);
    while(!A.empty() && flag && level < 5) {
        flag = 0;
        int step = CONSOL_SIZE / pow(2, level + 1);
        //cout << step << endl;
        //int index = step;
        for(int i = 0; i < pow(2, level); i++) {
            tmp = A.front();
            A.pop();
            probel(step - 3);
            //index += 2 * step;
            if (tmp == NULL) {
                A.push(NULL);
                A.push(NULL);
                probel(6);
            }
            else {
                printf("%s", tmp->word);
                probel(6 - strlen(tmp->word));
                A.push(tmp->left);
                A.push(tmp->right);
                flag = 1;
            }
            probel(step - 4);
            cout << " ";
        }
        cout << endl;
        cout << endl;
        level++;
    }
}
void probel(int n) {
    for(int i = 0; i < n; i++) {
        cout << " ";
    }
}
void BST::show(char c) {
    if(printable) {
        print_tree(head, c);
    }
    else {
        cout << "Cannot print tree, len of word is so big for it\n";
    }
}
void BST::show_as_tree(char c) {
    print(head, 0, true, c);
}
BST::~BST() {
    log("~");
    delete_tree(head);
    head = NULL;
}
void BST::delete_tree(element *tmp) {
    if(tmp) {
        delete_tree(tmp->left);
        delete_tree(tmp->right);
        delete tmp;
        tmp = NULL;
    }
}
BST::BST(const BST &obj) {
    log("copy");
    if(&obj != this) {
        *this = obj;
    }
}
BST::BST() {
    head = NULL;
    printable = true;
}

bool BST::find(char *str) {
    element *tmp = head;
    int cmp = 0;
    while(1) {
        if(!tmp) {
            return false;
        }
        cmp = strcmp(tmp->word, str);
        if(cmp == 0) { return true; }
        if(cmp < 0) {
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
int BST::for_find_letter(element *tmp, char c) {
    if(tmp) {
        if(tmp->word[0] == c) {
            cout << tmp->word << " ";
            return 1 + for_find_letter(tmp->left, c) + for_find_letter(tmp->right, c);
        }
        else if(tmp->word[0] > c) {
            return for_find_letter(tmp->left, c);
        }
        else {
            return for_find_letter(tmp->right, c);
        }
    }
    return 0;
}
int BST::find_letter(char c) {
    return for_find_letter(head, c);
    //cout << endl;
    //show_as_tree(c);
}

void BST::LRootR(element *tmp) {
    if (tmp) {
        LRootR(tmp->left);
        cout << tmp->word << " ";
        LRootR(tmp->right);
    }
}
void BST::LRRoot(element *tmp) {
    if (tmp) {
        LRootR(tmp->left);
        LRootR(tmp->right);
        cout << tmp->word << " ";
    }
}
void BST::RootLR(element *tmp) {
    if (tmp) {
        cout << tmp->word << " ";
        LRootR(tmp->left);
        LRootR(tmp->right);
    }
}
void BST::LeftRootRight() {
    LRootR(head);
    cout << endl;
}
void BST::LeftRightRoot() {
    LRRoot(head);
    cout << endl;
}
void BST::RootLeftRight() {
    RootLR(head);
    cout << endl;
}