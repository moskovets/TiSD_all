//
// Created by moskov on 02.10.16.
//
#include "BigDouble.h"
#include "BigInt.h"

int main(){
    BigDouble b;
    BigInt a;
    cout << "------------------------------" << endl;
    //999999999999999999999999999999
    cin >> a;
    if(!a.error_flag) {
        cin >> b;
        if(!b.error_flag) {
            if(b.isZero()) {
                cout << "Devided by zero!";
            }
            else {
                BigDouble res = a / b;
                if(!res.error_flag)
                    cout << res;
            }
        }
    }
}