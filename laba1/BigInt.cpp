//
// Created by moskov on 02.10.16.
//

#include "BigInt.h"

BigInt::BigInt() {
    n = 0;
    for(int i = 0; i < MAX_LEN; ++i)
        arr[i] = 0;
    error_flag = false;
    sign = 1; // "+"
}

istream& operator>> (istream &stream, BigInt &obj){
    obj = BigInt();
    int *l = NULL;
    char ch;
    bool flag_sign = false;
    stream.get(ch);
    if(ch == '\n') {
        //cout << "o";
        return stream >> obj;
    }
    while(ch != '\n')
    {
        if(!isdigit(ch)) {
            if ((ch == '+' or ch == '-') and l == NULL and flag_sign == false) {
                obj.sign *= (ch == '+' ? 1 : (-1));
                flag_sign = true;
            }
            else if (ch != ' ') {
                cout << "Error symbol\n";
                obj.error_flag = true;
                while(ch != '\n')
                    stream.get(ch);
                return stream;
            }
        }
        else {
            if(l == NULL) {
                l = obj.arr;
            }
            *l = ch - 48;
            l++;
            obj.n++;
        }
        //cout << ch;
        stream.get(ch);
    }
    if(l - obj.arr > MAX_LEN_TZ) {
        cout << "Error in input\n";
        obj.error_flag = true;
        return stream;
    }
    if(l == NULL && ch == '\n') {
        //cout << "k";
        return stream >> obj;
    }
    //cout << exp << " ";
    //if(l == NULL) { cout << "O_o" << endl; }
    //obj.exp -= (l - point);
    //cout << n << endl;
    reverse(obj.arr, obj.arr + obj.n);
    //if(ch != '\n') cin.get(ch);
    return stream;

}
