//
// Created by moskov on 17.10.16.
//

#include "MyRecord.h"

MyRecord::MyRecord() {

}
long int MyRecord::get_population() {
    return population;
}
void MyRecord::show() {
    cout << "Страна " << country << endl;
    cout << "НАСЕЛЕНИЕ " << population << endl;
    cout << "Столица " << capital << endl;
    cout << "Материк ";
    switch(cont) {
        case Africa: cout << "Africa" << endl; break;
        case Antarctica: cout << "Antarctica" << endl; break;
        case Asia: cout << "Asia" << endl; break;
        case Australia: cout << "Australia" << endl; break;
        case Europe: cout << "Europe" << endl; break;
        case North_America: cout << "North_America" << endl; break;
        case South_America: cout << "South_America" << endl; break;
    }
    cout << "Тип туризма: ";
    switch(kind) {
        case sport: cout << "спортивный" << endl; tourism.sport.show(); break;
        case beach: cout << "пляжный" << endl; tourism.beach.show(); break;
        case excursion: cout << "экскурсионный" << endl;  tourism.excursion.show(); break;
    }

}
void MyRecord::create_record() {
    char str[LEN_STRING];
    int x;
    int flag = 0;

    do {
        flag = 0;
        cout << "Введите название страны: ";
        cin >> str;
        if(string_check(str)) {
            strcpy(country, str);
        }
        else {
            flag = 1;
        }
    } while (flag);

    do {
        flag = 0;
        cout << "Введите количество жителей: ";
        cin >> str;
        char ** end = NULL;
        x = strtol(str, end, 10);
        if(x <= 0 || x == LONG_MAX) {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
        population = x;
    } while (flag);

    do {
        flag = 0;
        cout << "Введите столицу: ";
        cin >> str;
        if(string_check(str)) {
            strcpy(capital, str);
        }
        else {
            flag = 1;
        }
    } while (flag);

    do {
        flag = 0;
        cout << "Выберите материк: \n0-Africa, 1-Antarctica, 2-Asia, 3-Australia, 4-Europe, 5-North_America, 6-South_America: ";
        if(scanf("%d", &x) == 1 && x >= 0 && x <= 6) {
            cont = continents(x);
        }
        else {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
    } while (flag);

    do {
        flag = 0;
        cout << "Выберите вид туризма: 0 - экскурсионный 1 - пляжный 2 - спортивный : ";
        if(scanf("%d", &x) == 1) {
            switch(x) {
                case 0: tourism.excursion.create_excursion(); kind = excursion; break;
                case 1: tourism.beach.create_beach(); kind = beach; break;
                case 2: tourism.sport.create_sport(); kind = sport; break;
                default:
                    cout << "Ошибочный ввод" << endl;
                    flag = 1;
            }
        }
        else {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
    } while(flag);
}
int MyRecord::create_record_fromfile(istream& in) {
    char str[LEN_STRING];
    int x;
    int flag = 0;
    in >> str;
    if(string_check(str)) {
        strcpy(country, str);
    }
    else {
        cout << "error" << endl;
        return 1;
    }
    in >> str;
    char ** end = NULL;
    x = strtol(str, end, 10);
    if(x <= 0 || x == LONG_MAX)
        return 1;
    population = x;
    in >> str;
    if(string_check(str)) {
        strcpy(capital, str);
    }
    else return 1;
    in >> x;
    cont = continents(x);
    in >> x;
    switch(x) {
        case 0:
            in >> str;
            x = strtol(str, end, 10);
            if(x <= 0 || x == LONG_MAX) {
                return 1;
            }
            tourism.excursion.obj_count = x;
            in >> x;
            tourism.excursion.kind = kind_excursion(x);
            kind = excursion;
            break;
        case 1:
            in >> str;
            x = strtol(str, end, 10);
            if(x <= 0 || x == LONG_MAX) {
                return 1;
            }
            tourism.beach.time_fly = x;
            float tmp;
            in >> tmp;
            tourism.beach.temp_air = tmp;
            in >> tmp;
            tourism.beach.temp_water = tmp;
            in >> x;
            tourism.beach.season = seasons(x);
            kind = beach;
            break;
        case 2:
            in >> str;
            x = strtol(str, end, 10);
            if(x <= 0 || x == LONG_MAX) {
                return 1;
            }
            tourism.sport.min_cost = x;
            in >> x;
            tourism.sport.kind = kind_sport(x);
            kind = sport;
            break;
    }
    return 0;

}
void excursion_tourism::create_excursion() {
    int flag;
    char str[LEN_STRING];
    int x;
    do {
        flag = 0;
        cout << "Введите количество объектов: ";
        cin >> str;
        char ** end = NULL;
        x = strtol(str, end, 10);
        if(x <= 0 || x == LONG_MAX) {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
        obj_count = x;
    } while (flag);

    do {
        flag = 0;
        cout << "Выберите основной вид: \n0 - природа, 1 - история, 2 - искусство : ";
        if(scanf("%d", &x) == 1 && x >= 0 && x <= 2) {
            kind = kind_excursion(x);
        }
        else {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
    } while (flag);
}
void excursion_tourism::show() {
    cout << "Кол-во объектов: " << obj_count << endl;
    cout << "Вид: ";
    switch(kind) {
        case history: cout << "history" << endl; break;
        case nature: cout << "nature" << endl; break;
        case art: cout << "art" << endl; break;
    }
}
void sport_tourism::create_sport() {
    int flag;
    char str[LEN_STRING];
    int x;
    do {
        flag = 0;
        cout << "Введите минимальную стоимость отдыха: ";
        cin >> str;
        char ** end = NULL;
        x = strtol(str, end, 10);
        if(x <= 0 || x == LONG_MAX) {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
        min_cost = x;
    } while (flag);

    do {
        flag = 0;
        cout << "Выберите основной вид: \n0 - горные лыжи, 1 - серфинг, 2 - восхождения : ";
        if(scanf("%d", &x) == 1 && x >= 0 && x <= 2) {
            kind = kind_sport(x);
        }
        else {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
    } while (flag);

}
void sport_tourism::show() {
    cout << "Стоимость отдыха: " << min_cost << endl;
    cout << "Вид: ";
    switch(kind) {
        case skiing: cout << "skiing" << endl; break;
        case climbing: cout << "climbing" << endl; break;
        case surfing: cout << "surfing" << endl; break;
    }
}
void beach_tourism::create_beach() {
    int flag;
    char str[LEN_STRING];
    int x;
    do {
        flag = 0;
        cout << "Введите время полета до страны: ";
        cin >> str;
        char ** end = NULL;
        x = strtol(str, end, 10);
        if(x <= 0 || x == LONG_MAX) {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
        time_fly = x;
    } while (flag);

    do {
        flag = 0;
        float tmp;
        cout << "Введите температуру воздуха: ";
        if(scanf("%f", &tmp) && tmp >= -MAX_TEMPERATURE && tmp <= MAX_TEMPERATURE) {
            temp_air = tmp;
        }
        else {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
    } while (flag);

    do {
        flag = 0;
        float tmp;
        cout << "Введите температуру воды: ";
        if(scanf("%f", &tmp) && tmp >= -MAX_TEMPERATURE && tmp <= MAX_TEMPERATURE) {
            temp_water = tmp;
        }
        else {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
    } while (flag);

    do {
        flag = 0;
        cout << "Выберите основной сезон: \n 0-winter, 1-spring, 2-summer, 3-autumn : ";
        if(scanf("%d", &x) == 1 && x >= 0 && x <= 3) {
            season = seasons(x);
        }
        else {
            cout << "Ошибочный ввод" << endl;
            flag = 1;
        }
    } while (flag);

}
void beach_tourism::show() {
    cout << "Время полета: " << time_fly << endl;
    cout << "Температура воздуха и воды: " << temp_air << " " << temp_water << endl;
    cout << "Основной сезон: ";
    switch(season) {
        case winter: cout << "winter" << endl; break;
        case autumn: cout << "autumn" << endl; break;
        case spring: cout << "spring" << endl; break;
        case summer: cout << "summer" << endl; break;
    }

}
bool string_check(char* x) {
    for(int i = 0; i < strlen(x); ++i) {
        if(!isalpha(x[i])) {
            cout << "Error symbol in " << x << endl;
            return false;
        }
    }
    if(strlen(x) > LEN_STRING) {
        cout << "Превышено кол-во симоволов!" << endl;
        return false;
    }
    if(strlen(x) == 0) {
        cout << "Пустой ввод!" << endl;
        return false;
    }
    return true;
}

void show_skiing(MyRecord *arr, int n) {
    int flag = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i].kind == sport && arr[i].tourism.sport.kind == skiing) {
            arr[i].show();
            cout << endl;
            flag = 1;
        }
    }
    if(flag == 0) {
        cout << "Нет стран с горнолыжными курортами(" << endl;
    }
}

void buble_sort(MyRecord *begin, MyRecord* end) {

    for (MyRecord *i = begin; i < end; i++) {
        for (MyRecord *j = i + 1; j < end; j++) {
            if (i->population > j->population) {
                MyRecord tmp = *j;
                *j = *i;
                *i = tmp;
            }
        }
    }
}
void quick_sort(MyRecord *begin, MyRecord* end) {
    MyRecord *i = begin, *j = end, x = *(i + (j - i) / 2);

    do {
        while (i->population < x.population) i++;
        while (j->population > x.population) j--;

        if(i <= j) {
            if (i->population > j->population) {
                MyRecord tmp = *j;
                *j = *i;
                *i = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < end)
        quick_sort(i, end);
    if (begin < j)
        quick_sort(begin, j);
}
