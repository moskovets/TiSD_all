//
// Created by moskov on 04.11.16.
//

#include "CSparse_matrix.h"
CSparse_matrix& CSparse_matrix::operator=(const CSparse_matrix &obj) {
    //проверка на самоприсваивание
    if (this == &obj) {
        return *this;
    }
    if(n )
    if(IA_head) free_all(IA_head);
    NA = obj.NA;

    if(!JA.empty())JA.erase(JA.begin(), JA.end());
    if(!A.empty()) A.erase(A.begin(), A.end());
    for(int i = 0; i < NA; i++) {
        JA.push_back(obj.JA[i]);
        A.push_back(obj.A[i]);
    }
    n = obj.n;
    m = obj.m;
    IA_head = copy_list(obj.IA_head);
    return *this;
}
CSparse_matrix::CSparse_matrix() {
    IA_head = NULL;
    NA = n = m = 0;
}
int** CSparse_matrix::to_standart() {
    int **res = new int* [n];
    for(int i = 0; i < n; i++) {
        res[i] = new int [m];
    }
    my_list *tmp = IA_head;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            res[i][j] = 0;
        int A_begin = tmp->value;
        int A_end = tmp->next->value;
        for(int k = A_begin; k < A_end; k++) {
            res[i][JA[k]] = A[k];
            //cout << A[k] << " ";
        }
        tmp = tmp->next;
    }
    //cout << n << " " << m << endl;
    return res;
}
CSparse_matrix::CSparse_matrix(int narr, int marr, int **arr) {
    n = narr;
    m = marr;
    NA = 0;
    IA_head = NULL;
    my_list* IA_tail = NULL; //куда писать следующий список
    int flag = 0;
    for(int i = 0; i < n; i++) {
        my_list* tmp = create_node(NA);
        if(!IA_head) {
            IA_head = IA_tail = tmp;
        }
        else {
            IA_tail->next = tmp;
            IA_tail = IA_tail->next;
        }
        for(int j = 0; j < m; j++) {
            if(arr[i][j]) {
                A.push_back(arr[i][j]);
                JA.push_back(j);
                NA++;
                flag = 1;
            }
        }
        if(flag == 0) {
            tmp->value = INF;
        }
    }
    IA_tail->next = create_node(NA);
}

CSparse_matrix::CSparse_matrix(const CSparse_matrix &obj) {
    //cout << "a";
    *this = obj;
}
void CSparse_matrix::transposition() {
    vector <vector <int>> new_A (m);
    vector <vector <int>> new_JA (m);

    my_list *tmp_i = IA_head;
    //int j;
    int A_index = 0;
    for(int i = 0; i < n; i++) {
        int A_begin = tmp_i->value;
        int A_end = tmp_i->next->value;
        for(int k = A_begin; k < A_end; k++) {
            new_A[JA[k]].push_back(A[k]);
            new_JA[JA[k]].push_back(i);
        }
        tmp_i = tmp_i->next;
    }
    A.erase(A.begin(), A.end());
    JA.erase(JA.begin(), JA.end());
    free_all(IA_head);

    IA_head = NULL;
    my_list* IA_tail = NULL; //куда писать следующий список
    int flag = 0;

    for(int i = 0; i < m; i++) {
        my_list* tmp = create_node((int) A.size());
        if(!IA_head) {
            IA_head = IA_tail = tmp;
        }
        else {
            IA_tail->next = tmp;
            IA_tail = IA_tail->next;
        }

        for(int j = 0; j < new_A[i].size(); j++) {
            A.push_back(new_A[i][j]);
            JA.push_back(new_JA[i][j]);
            flag = 1;
        }
        if(flag == 0) {
            tmp->value = INF;
        }
    }
    NA = A.size();
    IA_tail->next = create_node(NA);
    swap(n, m);
}
CSparse_matrix CSparse_matrix::operator*(CSparse_matrix &obj) {
    CSparse_matrix res = CSparse_matrix();
    CSparse_matrix copy = obj;
    //copy = obj;
    //copy.show();
    copy.transposition();
    //copy.show();
    //vector <int> Av;
    //vector <int> JAv;
    res.IA_head = NULL;
    my_list* IA_tail = NULL; //куда писать следующий список

    my_list *tmp1_i = IA_head;
    int flag = 0;
    for(int i = 0; i < n; i++) {
        my_list* tmp = create_node((int) res.A.size());
        if(!res.IA_head) {
            res.IA_head = IA_tail = tmp;
        }
        else {
            IA_tail->next = tmp;
            IA_tail = IA_tail->next;
        }

        int A1_begin = tmp1_i->value;
        int A1_end = tmp1_i->next->value;
        my_list *tmp2_i = copy.IA_head;
        for(int j = 0; j < copy.n; j++) {
            int mult = 0;
            int A2_begin = tmp2_i->value;
            int A2_end = tmp2_i->next->value;
            for(int k1 = A1_begin, k2 = A2_begin; k1 < A1_end && k2 < A2_end; ) {
                if(JA[k1] == copy.JA[k2]) {
                    mult += A[k1] * copy.A[k2];
                    k1++;
                    k2++;
                }
                else if(JA[k1] < copy.JA[k2]) {
                    k1++;
                }
                else {
                    k2++;
                }
            }
            if(mult) {
                res.A.push_back(mult);
                res.JA.push_back(j);
                flag = 1;
            }
            tmp2_i = tmp2_i->next;
        }
        if(flag == 0) {
            tmp->value = INF;
        }
        tmp1_i = tmp1_i->next;
    }
    res.NA = (int)res.A.size();
    if(IA_tail)
        IA_tail->next = create_node(res.NA);
    else
        IA_tail = create_node(res.NA);
    res.n = n;
    res.m = obj.m;
    return res;
}

CSparse_matrix::~CSparse_matrix() {
    //delete[] A;
    //delete[] JA;
    free_all(IA_head);
}

void CSparse_matrix::show() {
    cout << "n m : " << n << " " << m << endl;
    cout << "A : ";
    //cout.precision(4);
    for(int i = 0; i < NA; i++) {
        cout << A[i] << " ";
    }
    cout << endl << "JA: ";
    for(int i = 0; i < NA; i++) {
        cout << JA[i] << " ";
    }
    cout << "\nIA_list: ";
    print_list(IA_head);
    cout << endl;
}
int CSparse_matrix::memory() {
    return NA * 2 + m;
}