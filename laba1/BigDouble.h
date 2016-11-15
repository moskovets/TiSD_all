//
// Created by moskov on 02.10.16.
//

#ifndef TISD_LABA1_BIGDOUBLE_H
#define TISD_LABA1_BIGDOUBLE_H
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include "BigInt.h"
using namespace std;

#define MAX_LEN 100
#define EXP_LIMIT 99999
#define MAX_LEN_TZ 30
class BigDouble {
private:
    int n;
    int arr[MAX_LEN];
    int exp;
    short int sign;

    void extend();
    void updateAsDevidend();
    void normalize();

public:
    bool error_flag;
    BigDouble();
    BigDouble(const BigDouble &obj);
    BigDouble(const BigInt obj);

    bool isZero();

    friend BigDouble operator*(const BigDouble &a, const int b);
    friend BigDouble operator-(const BigDouble &a, const BigDouble &b);
    friend BigDouble operator/(const BigInt &a, const BigDouble &b);
    friend bool operator <=(const BigDouble &a, const BigDouble &b);
    friend ostream& operator<< (ostream &stream, const BigDouble &obj);
    friend istream& operator>> (istream &stream, BigDouble &obj);
};

BigDouble operator*(const BigDouble &a, const int b);
BigDouble operator-(const BigDouble &a, const BigDouble &b);
BigDouble operator/(const BigInt &a, const BigDouble &b);
ostream& operator<< (ostream &stream, const BigDouble &obj);
istream& operator>> (istream &stream, BigDouble &obj);
bool operator <=(const BigDouble & a, const BigDouble & b);


#endif //TISD_LABA1_BIGDOUBLE_H
