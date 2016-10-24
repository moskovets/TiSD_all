
#include "library.h"
#include "CQueue_array.h"
#include "CQueue_list.h"
struct interval_time {
    double min;
    double max;
    interval_time(double a, double b) {
        min = a;
        max = b;
    }
};

double get_time(interval_time t) {
    return (t.max - t.min) * (double)(rand() / (double)RAND_MAX) + t.min;
}
template <typename T>
void work(int n, int interval, interval_time t1, interval_time t2, interval_time t3, interval_time t4, int flag) {
    T que1;
    T que2;

    double time = 0.0;
    int type = 0;
    double tr1, tr2, tr_obr;
    int req_in1 = 0, req_in2 = 0, req_out1 = 0, req_out2 = 0;
    int req_show = 0;
    tr1 = tr2 = tr_obr = 0.;
    while(req_out1 < n) {
        if(que1.is_full() or que2.is_full()) {
            cout << "Переполнение очереди!" << endl;
        }
        if (tr1 == 0.) {
            tr1 = get_time(t1);
        }
        if (tr2 == 0.) {
            tr2 = get_time(t2);
        }
        if(tr_obr == 0.) {
            switch(type) {
                case 0:
                    if (!que1.Empty_CQueue()) {
                        type = 1;
                        tr_obr = get_time(t3);
                        que1.PopFront();
                        //req_out++;
                    } else if (!que2.Empty_CQueue()) {
                        type = 2;
                        tr_obr = get_time(t4);
                        que2.PopFront();
                    }
                    break;
                case 1:
                    if (!que1.Empty_CQueue()) {
                        type = 1;
                        tr_obr = get_time(t3);
                        //req_out++;
                        que1.PopFront();
                    }
                    else if(!que2.Empty_CQueue()) {
                            type = 2;
                            tr_obr = get_time(t4);
                            que2.PopFront();
                    }
                    break;
                case 2:
                    if (!que2.Empty_CQueue()) {
                        type = 2;
                        tr_obr = get_time(t4);
                        que2.PopFront();
                    } else if (!que1.Empty_CQueue()) {
                        type = 1;
                        tr_obr = get_time(t3);
                        //req_out++;
                        que1.PopFront();
                    }
                    break;
            }
        }
        double tmin = 0.;
        if(tr_obr == 0.) {
            tmin = min(tr1, tr2);
        }
        else {
            tmin = min(tr1, min(tr2, tr_obr));
        }
        if(tmin == tr1 && tmin) {
            que1.PushBack(request());
            req_in1++;
        }
        if (tmin == tr2 && tmin) {
            que2.PushBack(request());
            req_in2++;
        }
        if(tmin == tr_obr && tmin) {
            tr_obr = 0.;
            if(type == 1) {
                req_out1++;
            }
            if(type == 2) {
                req_out2++;
            }
        }
        tr1 -= tmin;
        tr2 -= tmin;
        if(tr_obr >= tmin) { tr_obr -= tmin; }
        time += tmin;
        if(req_out1 % interval == 0 && req_out1 != req_show) {
            req_show = req_out1;
            cout << "Обработано (заявки 1-го типа) " << req_out1 << endl;
            que1.show();
            //que2.show();
            cout << "--------------------------------" << endl;
        }
    }
    cout << "Общее время моделирования " << time << endl;
    cout << "Кол-во вошедших и вышедших (1 тип) " << req_in1 << " " << req_out1 << endl;
    cout << "Кол-во вошедших и вышедших (2 тип) " << req_in2 << " " << req_out2 << endl;
    if(flag == 1) {
        cout << "Незадействованные адреса эл-тов:\n";
        que1.show_adr();
        que2.show_adr();
    }
}

int main()
{
    srand(time(0));
    int n = 1000;
    int interval = 100;
    interval_time t1(1, 5);
    interval_time t2(0, 3);
    interval_time t3(0, 4);
    interval_time t4(0, 1);

    int flag;
    int a;
    char ch;
    while(true)
    {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;

        cout << "0: Изменить параметры/Просмотреть текущие" << endl;
        cout << "1: Моделирование для очереди на массиве" << endl;
        cout << "2: Моделирование для очереди на списке" << endl;
        cout << "3: Закончить работу" << endl;
        cin >> a;
        switch(a)
        {
            case 0:
                cout << "Кол-во заявок первого типа " << n << endl;
                cout << "Интервал печати " << interval << endl;
                cout << "T1 " << t1.min << " " << t1.max << endl;
                cout << "T2 " << t2.min << " " << t2.max << endl;
                cout << "T3 " << t3.min << " " << t3.max << endl;
                cout << "T4 " << t4.min << " " << t4.max << endl;
                cout << "Изменить параметры? (y-yes) ";
                cin >> ch;
                if(ch == 'y') {
                    cout << "Кол-во заявок первого типа "; cin >> n;
                    cout << "Интервал печати "; cin >> interval;
                    cout << "T1 "; cin >> t1.min >> t1.max;
                    cout << "T1 "; cin >> t2.min >> t2.max;
                    cout << "T1 "; cin >> t3.min >> t3.max;
                    cout << "T1 "; cin >> t4.min >> t4.max;
                    if(n <= 0 || interval <= 0 || t1.min > t1.max || t1.min < 0 || t2.min > t2.max || t2.min < 0 ||
                                                  t3.min > t3.max || t3.min < 0 || t4.min > t4.max || t4.min < 0 )
                    {
                        cout << "Oшибка во вводе" << endl;
                        return 0;
                    }
                }
                break;
            case 1:
                work<CQueue_array>(n, interval, t1, t2, t3, t4, 0);
                break;
            case 2:
                cout << "Выводить информацию о фрагментации памяти? 1 - yes" << endl;
                cin >> flag;
                if(flag != 1)
                    flag = 0;
                work<CQueue_list>(n, interval, t1, t2, t3, t4, flag);
                break;
            case 3:
                cout << "До свиданья)" << endl;
                return 0;
            default:
                cout << "Команда не найдена";
                break;
        }
    }

    return 0;
}
