#include <iostream>
#include <fstream>
#include <time.h>
#include "Table_key.h"
#define MAX_RECORD_ARR 210
int test() {
    MyRecord arr[100];
    ifstream inp;
    inp.open("/home/moskov/ClionProjects/TiSD/laba3/table.txt");
    if(!inp.is_open()) { cout << "er"; }
    int n;
    inp >> n;
    for(int i = 0; i < n; i++) {
        if(arr[i].create_record_fromfile(inp) == 1) {
            cout << i << " " << "return" << endl;
        }
    }
    for(int i = 0; i < n; i++) {
        arr[i].show();
        cout << endl;
    }
    cout << "-------------------" << endl;
    show_skiing(arr, n);
    cout << "---------------------------------------" << endl;
    buble_sort(arr, arr + n);

    //quick_sort(arr, arr + n - 1);
    for(int i = 0; i < n; i++) {
        arr[i].show();
        cout << endl;
    }
/*
    Table_key keys[100];
    for(int i = 0; i < n; i++) {
        keys[i] = Table_key(i, arr[i]);
    }
    for(int i = 0; i < n; i++) {
        cout << keys[i].id;
    }
    cout << endl;
    //buble_sort(keys, keys + n);
    quick_sort(keys, keys + n - 1);
    for(int i = 0; i < n; i++) {
        cout << keys[i].id;
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        arr[keys[i].id].show();
    }
    cout << "---------------------------------------" << endl;
*/
    return 0;
}
int main() {
    int a;
    int x;
    time_t t1, t2, t3, t4;
    MyRecord arr[MAX_RECORD_ARR];
    ifstream inp;
    inp.open("/home/moskov/ClionProjects/TiSD/laba3/table.txt");
    if(!inp.is_open()) { cout << "Cannot open file" << endl; }
    int n;
    inp >> n;
    for(int i = 0; i < n; i++) {
        if(arr[i].create_record_fromfile(inp) == 1) {
            cout << i << " " << "return" << endl;
        }
    }
    Table_key keys[MAX_RECORD_ARR];
    while(true)
    {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;

        cout << "0: Показать таблицу" << endl;
        cout << "1: Отсортировать таблицу по ключам (не меняя исходную)" << endl;
        cout << "2: Отсортировать таблицу" << endl;
        cout << "3: Добавить запись" << endl;
        cout << "4: Удалить запись" << endl;
        cout << "5: Сравнить эффективность сортировки таблицы и ключей" << endl;
        cout << "6: Сравнить эффективность сортировок (для таблиц по ключам)" << endl;
        cout << "7: Вывести список горнолыжных курортов" << endl;
        cout << "8: Закончить работу" << endl;
        cin >> a;
        switch(a)
        {
            case 0:
                for(int i = 0; i < n; i++) {
                    arr[i].show();
                    cout << endl;
                }
                break;
            case 1:
                for(int i = 0; i < n; i++) {
                    keys[i] = Table_key(i, arr[i]);
                }
                for(int i = 0; i < n; i++) {
                    cout << keys[i].id << " ";
                }
                cout << endl;
                //buble_sort(keys, keys + n);
                quick_sort(keys, keys + n - 1);
                for(int i = 0; i < n; i++) {
                    cout << keys[i].id << " ";
                }
                cout << endl;
                for(int i = 0; i < n; i++) {
                    arr[keys[i].id].show();
                    cout << endl;
                }
                break;
            case 2:
                quick_sort(arr, arr + n - 1);
                for(int i = 0; i < n; i++) {
                    arr[i].show();
                    cout << endl;
                }
                break;
            case 3:
                if(n >= MAX_RECORD_ARR - 1) {
                    cout << "Переполнение массива записей" << endl;
                    break;
                }
                arr[n].create_record();
                n++;
                break;
            case 4:
                cout << "Введите индекс удаляемой записи от 0 до " << n - 1;
                cin >> x;
                if(x < 0 && x >= n) {
                    cout << "выход из дапазона" << endl;
                    break;
                }
                for(int i = x; i < n; i++) {
                    arr[i] = arr[i + 1];
                }
                cout << "Эл-т удален" << endl;
                n--;
                break;
            case 5:
                for(int i = 0; i < n; i++) {
                    keys[i] = Table_key(i, arr[i]);
                }
                t1 = clock();
                quick_sort(keys, keys + n - 1);
                t2 = clock();
                t3 = clock();
                quick_sort(arr, arr + n - 1);
                t4 = clock();
                cout << "Время работы сортировки по ключам: " << t2 - t1 << endl;
                cout << "Время работы сортировки таблицы: " << t4 - t3 << endl;
                break;
            case 6:
                for(int i = 0; i < n; i++) {
                    keys[i] = Table_key(i, arr[i]);
                }
                t1 = clock();
                quick_sort(keys, keys + n - 1);
                t2 = clock();
                for(int i = 0; i < n; i++) {
                    keys[i] = Table_key(i, arr[i]);
                }
                t3 = clock();
                buble_sort(keys, keys + n);
                t4 = clock();
                cout << "Время работы сортировки пузырьком: " << t4 - t3 << endl;
                cout << "Время работы быстрой сортировки: " << t2 - t1 << endl;
                break;
            case 7:
                show_skiing(arr, n);
                break;
            case 8:
                cout << "До свиданья)" << endl;
                return 0;
            default:
                cout << "Команда не найдена";
                break;
        }
    }
    return 0;
}