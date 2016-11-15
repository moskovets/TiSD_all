//
// Created by moskov on 02.10.16.
//

#ifndef TISD_LABA1_BIGINT_H
#define TISD_LABA1_BIGINT_H

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_LEN 100
#define MAX_LEN_TZ 30

class BigInt {
public:
    int n;
    int arr[MAX_LEN];
    short int sign;
    bool error_flag;
    BigInt();

    friend istream& operator>> (istream &stream, BigInt &obj);
};
istream& operator>> (istream &stream, BigInt &obj);


#endif //TISD_LABA1_BIGINT_H
