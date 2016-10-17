//
// Created by moskov on 17.10.16.
//

#ifndef LABA3_MYRECORD_H
#define LABA3_MYRECORD_H

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <climits>
using namespace std;
#define LEN_STRING 50
#define MAX_TEMPERATURE 50

enum continents { Africa, Antarctica, Asia, Australia, Europe, North_America, South_America } ;
enum kind_excursion { nature, history, art } ;
enum kind_sport { skiing, surfing, climbing } ;
enum union_tourism { excursion, sport, beach } ;
enum seasons { winter, spring, summer, autumn } ;

struct excursion_tourism {
    int obj_count;
    kind_excursion kind;
    void create_excursion();
    void show();
};
struct beach_tourism {
    float temp_water;
    float temp_air;
    int time_fly;
    seasons season;
    void create_beach();
    void show();
};
struct sport_tourism {
    kind_sport kind;
    int min_cost;
    void create_sport();
    void show();
};
union kind_tourism {
    excursion_tourism excursion;
    beach_tourism beach;
    sport_tourism sport;
};

class MyRecord {
private:
    char country[LEN_STRING];
    long int population;
    char capital[LEN_STRING];
    continents cont;
    union_tourism kind;
    kind_tourism tourism;

public:
    friend void show_skiing(MyRecord *arr, int n);
    friend void buble_sort(MyRecord *begin, MyRecord* end);
    friend void quick_sort(MyRecord *begin, MyRecord* end);
    MyRecord();
    void create_record();
    int create_record_fromfile(istream& out);
    void show();
    long int get_population();

};
void show_skiing(MyRecord *arr, int n);
//sort 1, sort 2
//skiing
bool string_check(char* x);
void buble_sort(MyRecord *begin, MyRecord* end);
void quick_sort(MyRecord *begin, MyRecord* end);

#endif //LABA3_MYRECORD_H
