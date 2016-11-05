#include "library.h"
#include "CSparse_matrix.h"

/*
 * Заранее прошу прощения у всех, кто решит разобраться в этом коде, возможно, я добавлю комментарии)
 */
int** mult_standart(int** arr1, int n1, int m1, int** arr2, int n2, int m2)
{
    assert(m1 == n2);
    int** res = new int* [n1];
    for(int i = 0; i < n1; i++) {
        res[i] = new int [m2];
    }
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m2; j++) {
            res[i][j] = 0;
            for(int k = 0; k < n2; k++) {
                res[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    return res;
}
int** mult_vector(int** arr1, int n1, int m1, int** arr2, int n2, int m2)
{
    assert(m1 == n2);
    CSparse_matrix a1(n1, m1, arr1);
    CSparse_matrix a2(n2, m2, arr2);
    //cout << "ok" << endl;
    CSparse_matrix res = a1 * a2;
    //cout << "ok2" << endl;
    //res.show();
    return res.to_standart();
}

bool equal_matrix(int** a, int** b, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i][j] != b[i][j])
                return false;
        }
    }
    return true;
}

int rand_int(int n) {
    return (int) ((rand() / (double) RAND_MAX) * (double) n);
}
int **generate(int n, int m, double percent, int l, int r) {
    int col = n * m * percent / 100;
    int ** matr = new int* [n];
    for(int i = 0; i < n; i++) {
        matr[i] = new int[m];
        for(int j = 0; j < m; j++) {
            matr[i][j] = 0;
        }
    }
    for(int i = 0; i < col; i++) {
        matr[rand_int(n)][rand_int(m)] = rand_int(r - l) + l;
    }
    return matr;
}

void free_matr(int **a, int n) {
    for(int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete a;
}
void print_matr(int **a, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int my_main() {
    srand(time(0));
    int n1 = 6;
    int n2 = 4;
    int **a1 = generate(6, 4, 100, 0, 10);
    /*for(int i = 0; i < n1; i++) {
        for(int j = 0; j < n2; j++) {
            cout << a1[i][j] << " ";
        }
        cout << endl;
    }*/
    /*CSparse_matrix a = CSparse_matrix(n1, n2, a1);
    a.show();
    a.transposition();
    a.show();
    a.transposition();
    cout << "ok" << endl;
    int **r = a.to_standart();

    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < n2; j++) {
            cout << r[i][j] << " ";
        }
        cout << endl;
    }
    cout << "ko" << endl;
    cout << equal_matrix(a1, r, n1, n2);
    //free_matr(a1, n1);
    free_matr(r, n1);
    cout << "tut" << endl;
*/

    int **a2 = generate(4, 5, 100, 0, 10);
    /*for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            cout << a2[i][j] << " ";
        }
        cout << endl;
    }
    cout << "sdfsd" << endl;*/
    int **res_1 = mult_standart(a1, 6, 4, a2, 4, 5);
    /*for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 5; j++) {
            cout << res_1[i][j] << " ";
        }
        cout << endl;
    }
    cout << "kok" << endl;*/
    int **res_2 = mult_vector(a1, 6, 4, a2, 4, 5);
    cout << equal_matrix(res_1, res_2, 6, 5);
    //cout << "ok" << endl;
    free_matr(a1, 6);
    free_matr(a2, 4);
    free_matr(res_1, 6);
    free_matr(res_2, 6);
    return 0;

}
int ** hand_input(int* n, int* m) {
    int **a = new int* [*n];
    for(int i = 0; i < *n; i++) {
        a[i] = new int [*m];
        for(int j = 0; j < *m; j++) {
            a[i][j] = 0;
        }
    }
    cout << "Введите по 3 числа для каждого ненулевого эл-та (номер строки, столбца начиная с нуля, значение)\n ";
    while(1) {
        while (1) {
            int i = *n + 1, j = *m + 1, k = 0;
            if (scanf("%d %d %d", &i, &j, &k)) {
                if ((i >= 0) && (i < *n) && (j >= 0) && (j < *m)) {
                    a[i][j] = k;
                    break;
                }
            }
            cout << "error, попробуйте еще раз:  ";
        }
        cout << "Продолжить (1-нет)? ";
        char ch;
        cin >> ch;
        if (ch == '1') {
            break;
        }
    }
    return a;
}
int ** auto_input(int* n, int* m) {
    double percent = -1;
    cout << "Введите процент заполнения(вещественное число) [0, 100]: ";
    while(!(scanf("%lf", &percent) && (percent >= 0) && (percent <= 100))) {
        cout << "error, попробуйте еще раз:  ";
        percent = -1;
    }
    cout << "Выберите диапазон значений [" << -R_MAX << ", " << R_MAX << "]: " << endl;
    int l, r;
    l = r = R_MAX + 1;
    cout << "Начало диапазона значений: " << endl;
    while(!(scanf("%d", &l) && (l >= -R_MAX) && (l <= R_MAX))) {
        cout << "error, попробуйте еще раз:  ";
        l = R_MAX + 1;
    }

    cout << "Конец диапазона значений: " << endl;
    while(!(scanf("%d", &r) && (r >= -R_MAX) && (r <= R_MAX) && (l <= r))) {
        cout << "error, попробуйте еще раз:  ";
        r = R_MAX + 1;
    }
    return generate(*n, *m, percent, l, r);
}

int ** input_matr(int *n, int *m) {
    int tmp;
    //*n = 0;
    cout << "Марица\n";
    /*cout << "Введите кол-во строк [1, " << MAX_SIZE << "]: ";
    while(!(scanf("%d", n) && (*n >= 1) && (*n <= MAX_SIZE))) {
        cout << "error, попробуйте еще раз:  ";
        *n = 0;
    }*/
    cout << "Введите кол-во столбцов [1, " << MAX_SIZE << "]: ";
    *m = 0;
    while(!(scanf("%d", m) && (*m >= 1) && (*m <= MAX_SIZE))) {
        cout << "error, попробуйте еще раз:  ";
        *m = 0;
    }
    cout << "Выберите ввод ручной(1) или автоматический(2)" << endl;
    cin >> tmp;
    while(tmp != 1 && tmp != 2) { cout << "Неверная команда, исправьте"; cin >> tmp; }
    if(tmp == 1) {
        return hand_input(n, m);
    }
    else {
        return auto_input(n, m);
    }
}
int ** input_string(int *n, int *m) {
    int tmp;
    *n = 1;
    cout << "Ввод вектора-строки\n";
    cout << "Введите кол-во столбцов [1, " << MAX_SIZE << "]: ";
    *m = 0;
    while(!(scanf("%d", m) && (*m >= 1) && (*m <= MAX_SIZE))) {
        cout << "error, попробуйте еще раз:  ";
        *m = 0;
    }
    cout << "Выберите ввод ручной(1) или автоматический(2)" << endl;
    cin >> tmp;
    while(tmp != 1 && tmp != 2) { cout << "Неверная команда, исправьте"; cin >> tmp; }
    if(tmp == 1) {
        return hand_input(n, m);
    }
    else {
        return auto_input(n, m);
    }
}
void work_hand() {
    cout << "**************************************************************" << endl;
    cout << "Данная программа умножает вектор-строку на матрицу:" << endl;
    int ** a;
    int na, ma;
    int ** b;
    int nb, mb; //ma == nb!!!!!!!!!!!!!!
    int tmp;
    a = input_string(&na, &ma);
    nb = ma;
    b = input_matr(&nb, &mb);
    CSparse_matrix A(na, ma, a);
    CSparse_matrix B(nb, mb, b);
    CSparse_matrix RES = A * B;
    char ch;
    int flag = 1;
    int ** R;
    int ** res;
    while(flag) {
        cout << "0: Показать первую матрицу в разреженном формате" << endl;
        cout << "1: Показать вторую матрицу в разреженном формате" << endl;
        cout << "2: Показать результат умножения в разреженном формате" << endl;
        cout << "3: Показать первую матрицу в стандартном формате" << endl;
        cout << "4: Показать вторую матрицу в стандартном формате" << endl;
        cout << "5: Показать результат в стандартном формате" << endl;
        cout << "6: Показать результат работы стандартного алгоритма" << endl;
        cout << "7: Закончить работу с введенной парой матриц" << endl;
        cin >> ch;
        //cout << ch << endl;
        switch(ch) {
            case '0': A.show(); break;
            case '1': B.show(); break;
            case '2': RES.show(); break;
            case '3': print_matr(a, na, ma); break;
            case '4': print_matr(b, nb, mb); break;
            case '5':
                R = RES.to_standart();
                print_matr(R, na, mb);
                free_matr(R, na);
                break;
            case '6':
                res = mult_standart(a, na, ma, b, nb, mb);
                print_matr(res, na, mb);
                free_matr(res, na);
                break;
            case '7':
                flag = 0;
                break;
            default: cout << "Error"; break;
        }
    }
    free_matr(a, na);
    free_matr(b, nb);
}
struct res_comp {
    int memory_standart;
    int memory_sparse;
    long long time_standart;
    long long time_sparse;
    double percent;
};
int compare() {
    int i, j, k;
    cout << "Введите кол-во строк и столбцов первой матрицы и кол-во столбцов второй [1, " << MAX_SIZE << "]: ";
    i = j = k = 0;
    while(true) {
        if (scanf("%d %d %d", &i, &j, &k)) {
            if ((i >= 1) && (i <= MAX_SIZE) && (j >= 1) && (j <= MAX_SIZE) && (k >= 1) && (k <= MAX_SIZE)) {
                break;
            }
            i = j = k = 0;
        }
    }
    double percent = -1;
    cout << "Введите процент заполнения(вещественное число) [0, 100]: ";
    while(!(scanf("%lf", &percent) && (percent >= 0) && (percent <= 100))) {
        cout << "error, попробуйте еще раз:  ";
        percent = -1;
    }
    int **a = generate(i, j, percent, -R_MAX, R_MAX);
    int **b = generate(j, k, percent, -R_MAX, R_MAX);

    CSparse_matrix A(i, j, a);
    //cout << "oooo" << endl;
    CSparse_matrix B(j, k, b);

    time_t t1 = clock();
    CSparse_matrix RES = A * B;
    time_t t2 = clock();
    cout << "Время умножения в разреженном виде: "  << t2 - t1 << endl;

    time_t t3 = clock();
    int ** res = mult_standart(a, i, j, b, j, k);
    time_t t4 = clock();
    cout << "Время умножения в стандартном виде: "  << t4 - t3 << endl;

    cout << "Память, необходимая для хранения стандартной матрицы " << (i * j) * sizeof(int) << endl;
    cout << "Память, необходимая для хранения разряженной матрицы " << A.memory() << endl;
    //A.show();
    free_matr(a, i);
    free_matr(b, j);
    free_matr(res, i);

}
res_comp my_compare(int n, double percent) {
    int i, j, k;
    i = j = k = n;
    int **a = generate(i, j, percent, -R_MAX, R_MAX);
    int **b = generate(j, k, percent, -R_MAX, R_MAX);

    CSparse_matrix A(i, j, a);
    CSparse_matrix B(j, k, b);

    time_t t1 = clock();
    CSparse_matrix RES = A * B;
    time_t t2 = clock();

    time_t t3 = clock();
    int ** res = mult_standart(a, i, j, b, j, k);
    time_t t4 = clock();
    res_comp r_c;
    r_c.memory_sparse = A.memory();
    r_c.memory_standart = (i * j) * sizeof(int);
    r_c.percent = percent;
    r_c.time_sparse = t2 - t1;
    r_c.time_standart = t4 - t3;
    //A.show();
    free_matr(a, i);
    free_matr(b, j);
    free_matr(res, i);
    return r_c;

}
int main2() {
    for(double i = 0.01; i <= 10; i *= 5) {
        res_comp r = my_compare(500, i);
        cout << r.percent << " " << r.time_standart << " " << r.time_sparse << " "
            << r.memory_standart << " " << r.memory_sparse << endl;
    }
}
int main() {
    srand(time(0));

    setlocale(LC_CTYPE, "rus");
    while(true) {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;
        cout << "0: Работа с матрицами" << endl;
        cout << "1: Сравнение скорости работы стандартного алгоритма и работы с разряженными матрицами" << endl;
        cout << "2: Exit" << endl;
        int ch;
        cin >> ch;
        switch(ch) {
            case 0:
                work_hand();
                break;
            case 1:
                compare();
                break;
            case 2:
                return 0;
            default:
                cout << "Error code" << endl;
                break;
        }
    }
    return 0;
}