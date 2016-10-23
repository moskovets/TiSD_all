
#include "library.h"
#include "CQueue_array.h"
#include "CQueue_list.h"

class OA {

};
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
void work(int n, int interval, interval_time t1, interval_time t2, interval_time t3, interval_time t4) {
    CQueue_array que1;
    CQueue_array que2;

    double time = 0.0;
    int type = 0;
    double tr1, tr2, tr_obr;
    int req_in = 0, req_out = 0;
    int req_show = 0;
    tr1 = tr2 = tr_obr = 0.;
    while(req_out < n) {
         //cout << time << " " << req_out << endl;
        //if(req_in >= n) { tr1 = MAX_RAND; }
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
        double tmin;
        if(tr_obr == 0.) {
            tmin = min(tr1, tr2);
        }
        else {
            tmin = min(tr1, min(tr2, tr_obr));
        }
        if(req_in <= n) {
            if(tmin == tr1) {
                que1.PushBack(request());
                req_in++;
            }
            if (tmin == tr2) {
                que2.PushBack(request());
            }
        }
        else if(tr_obr != 0.) {
            tmin = tr_obr;
        }
        if(tmin == tr_obr) {
            tr_obr = 0.;
            if(type == 1) {
                req_out++;
            }
        }
        tr1 -= tmin;
        tr2 -= tmin;
        time += tmin;
        if(req_in % interval == 0 && req_in != req_show) {
            req_show = req_in;
            que1.show();
            cout << req_out << endl;
        }
    }
}
int main()
{
    srand(time(0));
    int n = 1000;
    int interval = 100;
    work(n, interval, interval_time(1,5), interval_time(0,3), interval_time(0,4), interval_time(0,2));
    return 0;
}
