//
// Created by moskov on 02.10.16.
//

#include "BigDouble.h"

void BigDouble::extend() {
    for (int i = n; i >= 1; i--)
        arr[i] = arr[i-1];
    arr[0] = 0;
    if (arr[n])
        n++;
}

void BigDouble::updateAsDevidend() {
    for(int i = 0; i < n; i++) {
        arr[i+50] = arr[i];
    }
    for(int i = 0; i < 50; i++) {
        arr[i] = 0;
    }
    n += 50;
    exp -= 50;
}

BigDouble::BigDouble() {
    n = 0;
    for(int i = 0; i < MAX_LEN; ++i)
        arr[i] = 0;
    exp = 0;
    error_flag = false;
    sign = 1; // "+"
}
BigDouble::BigDouble(const BigDouble &obj) {
    n = obj.n;
    for(int i = 0; i < MAX_LEN; ++i)
        arr[i] = obj.arr[i];
    exp = obj.exp;
    error_flag = obj.error_flag;
    sign = obj.sign;
}
BigDouble::BigDouble(const BigInt obj) {
    n = obj.n;
    for(int i = 0; i < MAX_LEN; ++i)
        arr[i] = obj.arr[i];
    exp = 0;
    //exp = n;
    error_flag = obj.error_flag;
    sign = obj.sign;
}

ostream& operator<<(ostream &stream, const BigDouble &obj) {
    BigDouble obj_copy = BigDouble(obj);
    //obj_copy.normalize();
    stream << ((obj_copy.sign == 1) ? "+" : "-") << "0.";
    for(int i = obj_copy.n - 1; i >= 0 && i >= (obj_copy.n - 31); i--)
        stream << obj_copy.arr[i];
    stream << " E " << obj_copy.exp << endl;
    return stream;
}
void BigDouble::normalize() {
    int i = 0;

    while(n > 0 && arr[n-1] == 0) n--;
    exp += n;
    while(arr[i] == 0 && i < n)
        i++;
    for(int j = i; j < n+MAX_LEN_TZ; j++) {
        arr[j - i] = arr[j];
    }
    n -= i;
    if(n <= 0) n = 1;
    reverse(arr, arr + n);
    //exp += i;
    if(exp < 0 && abs(exp) > EXP_LIMIT) {
        int sdwig = EXP_LIMIT - exp;
        if(sdwig <= 30) {
            for (i = 0; i < n; i++) {
                arr[i + sdwig] = arr[i];
            }
            for(i = 0; i < sdwig; ++i) {
                arr[i] = 0;
            }
        }
        else {
            for(i = 0; i < MAX_LEN_TZ; i++)
                arr[i] = 0;
        }
        exp = -EXP_LIMIT;
        n = MAX_LEN_TZ;
    }
    while(1) {
        if (exp > 0 && exp > EXP_LIMIT) {
            cout << "Out of range\n";
            error_flag = true;
            return;
        }
        int arr_help[MAX_LEN];
        for (i = 0; i <= MAX_LEN_TZ + 1; i++) {
            arr_help[i] = arr[i];
        }
        i = MAX_LEN_TZ - 1;
        arr_help[i] += arr_help[MAX_LEN_TZ] >= 5 ? 1 : 0;
        while (i > 0 && arr_help[i] > 9) {
            arr_help[i--] %= 10;
            arr_help[i] += 1;
        }
        if (i == 0 && arr_help[i] > 9) {
            this->extend();
            exp += 1;
        }
        else {
            //cout << exp << endl;
            if (exp > 0 && exp > EXP_LIMIT) {
                cout << "Out of range\n";
                error_flag = true;
                return;
            }
            for (i = 0; i < MAX_LEN_TZ; i++) {
                arr[i] = arr_help[i];
            }
            n = MAX_LEN_TZ;
            break;
        }

    }
    reverse(arr, arr + n);
//999999999999999999999999999999
}
istream& operator>>(istream &stream, BigDouble &obj) {
    obj = BigDouble();
    bool flag_sign = false;
    int *l = NULL, *point = NULL;
    char ch;
    //string s;
    stream.get(ch);
    //cout << "j";
    if(ch == '\n')
        return stream >> obj;
    while(ch != 'e' && ch != 'E' && ch != '\n')
    {
        if(!isdigit(ch)) {
            if ((ch == '+' or ch == '-') and l == NULL and flag_sign == false) {
                obj.sign *= (ch == '+' ? 1 : (-1));
                flag_sign = true;
            } else if (ch == '.' and point == NULL) {
                point = l == NULL ? obj.arr : l;
            } else if (ch != ' ') {
                cout << "Error symbol\n";
                while(ch != '\n')
                    stream.get(ch);
                obj.error_flag = true;
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
    // final
    if (tolower(ch) == 'e' and scanf("%d", &obj.exp) != 1) {
        cout << "Error in input\n";
        while(ch != '\n')
            stream.get(ch);
        obj.error_flag = true;
        return stream;
    }
    if((l - obj.arr > MAX_LEN_TZ) or (abs(obj.exp) > EXP_LIMIT)) {
        cout << "Error in input\n";
        obj.error_flag = true;
        return stream;
    }
    //cout << "a";
    if(l == NULL && ch == '\n') ///???
        return stream >> obj;
    //cout << "b";
    if(point == NULL)
        point = l;
    //cout << exp << " ";
    //if(l == NULL) { cout << "O_o" << endl; }
    obj.exp -= (l - point);
    //obj.exp += obj.n;
    //cout << n << endl;
    reverse(obj.arr, obj.arr + obj.n);
    int i = obj.n - 1;
    while(i > 0 && obj.arr[i] == 0) {
        i--;
        obj.n--;
    }
    //if(ch != '\n') cin.get(ch);
    return stream;
}

bool operator <=(const BigDouble & a, const BigDouble & b) {
    if (a.n != b.n)
        return a.n < b.n;
    for (int i = a.n - 1; i >= 0; i--)
    {
        if (a.arr[i] != b.arr[i])
            return a.arr[i] < b.arr[i];
    }
    return true;
}

BigDouble operator*(const BigDouble &a, const int b) {
    BigDouble res;
    res.n = a.n;
    int r = 0;
    for (int i = 0; i < res.n | r; i++)
    {
        res.arr[i] = a.arr[i] * b + r;
        r = res.arr[i] / 10;
        res.arr[i] -= r * 10;
    }
    //cout << res.n << " " << endl;
    while (res.arr[res.n])
        res.n++;
    return res;
}
BigDouble operator-(const BigDouble &a, const BigDouble &b) {
    BigDouble res = a;
    int r = 0;
    for (int i = 0; i < res.n; i++)
    {
        res.arr[i] -= b.arr[i];
        //cout << res.arr[i] << " ";
        if (res.arr[i] < 0)
        {
            res.arr[i] += 10;
            res.arr[i + 1]--;
        }
    }
    //cout << endl;
    int pos = res.n-1;
    while (pos && !res.arr[pos])
        pos--;
    res.n = pos + 1;
    return res;
}
BigDouble operator/(const BigInt &a, const BigDouble &b) {
    BigDouble res;
    BigDouble tmp;
    BigDouble a_copy = BigDouble(a);
    //cout << a_copy << b;
    a_copy.updateAsDevidend();
    tmp.n = 1;
    for (int i = a_copy.n - 1; i >= 0; i--)
    {
        tmp.extend();
        tmp.arr[0] = a_copy.arr[i];
        int x = 0;
        int l = 0, r = 9;
        //cout << "i " << i << endl;
        while (l <= r)
        {
            int m = (l + r) >> 1;
            //cout << "m " << m << endl;
            BigDouble cur = b * m;
            //cur.print();
            //tmp.print();
            if (cur <= tmp)
            {
                x = m;
                l = m + 1;
            }
            else
                r = m - 1;
            //cout << l << " " << x << " " << r << endl;
        }
        res.arr[i] = x;
        //cout << " " << x << endl;
        BigDouble mul = b * x;
        tmp = tmp - mul;
        //cout << tmp << endl;
    }
    res.n = a_copy.n;
    int pos = a_copy.n;
    while (pos >= 0 && !res.arr[pos])
        pos--;
    res.n = pos + 1;
    res.exp = a_copy.exp - b.exp;
    res.sign = a_copy.sign * b.sign;
    //cout << res;

    res.normalize();
    return res;

}

bool BigDouble::isZero() {
    for(int i = 0; i < n; i++) {
        if(arr[i] != 0) {
            return false;
        }
    }
    return true;
}
