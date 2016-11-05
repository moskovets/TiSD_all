//
// Created by moskov on 04.11.16.
//

#ifndef LABA5_CSPARSE_MATRIX_H
#define LABA5_CSPARSE_MATRIX_H

#include "library.h"
#include "CList.h"
class CSparse_matrix {
private:
    vector <int> A;
    vector <int> JA;
    int NA;
    int n;
    int m;
    my_list* IA_head = NULL;
public:
    CSparse_matrix();
    CSparse_matrix(int narr, int marr, int **arr);
    CSparse_matrix(const CSparse_matrix &obj);
    void transposition();
    CSparse_matrix operator* (CSparse_matrix &obj);
    CSparse_matrix& operator=(const CSparse_matrix& obj);
    ~CSparse_matrix();
    void show();
    int memory();
    int** to_standart();
};


#endif //LABA5_CSPARSE_MATRIX_H
