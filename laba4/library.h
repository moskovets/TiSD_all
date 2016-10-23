//
// Created by moskov on 23.10.16.
//

#ifndef LABA4_LIBRARY_H
#define LABA4_LIBRARY_H

//#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define START_SIZE 1000
#define MAX_MEMORY 100

using namespace std;

typedef struct {
    //int time_in = 0;
    //int time_out = 0;
} request;

struct info_queue_request {
    int tmp_size = 0;
    int sum_size = 0;
    int count_request = 0;
    //int in_request = 0;
    //int out_request = 0;
    //int sum_time = 0;
};

#endif //ALGO4_LIBRARY_H
